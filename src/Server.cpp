/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:47:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/11 10:51:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const std::string &password, const int &port) 
    : port(port), password(password) {}

void Server::add_fd(int fd) {
    struct pollfd a;
    a.fd = fd;
    a.events = POLLIN;
    c_fds.push_back(a);
    // this->fds[this->clients_num].fd = fd;
    // this->fds[this->clients_num].events = POLLIN;
    // this->clients_num++;
}

const std::string& Server::getPassword() const {
    return (this->password);
}
const std::map<int, Client*>& Server::getClients() const {
    return (this->clients);
}

void Server::new_client(sockaddr *a, socklen_t len, int fd) {
    int client_fd = accept(fd, a, &len);
    if (client_fd == -1)
        throw std::exception();
    std::cout << BLUE << "Accepted connection from " << inet_ntoa(reinterpret_cast<struct sockaddr_in*>(a)->sin_addr) << RESET << std::endl;
    add_fd(client_fd);
    Client *client = new Client(client_fd);
    clients.insert(std::make_pair(client_fd, client));
}

void Server::auth(std::string &data, Client &client) {
    std::string key, value;
    std::stringstream str(data);
    str >> key;
    str >> value;
    ACommand *cmds[2] = {new Pass(), new Nick()};
    int i = (key == "PASS") * 1 + (key == "NICK") * 2;
    if (!i || i >= 3)
        return ;
    try { cmds[i - 1]->exec(value, client, *this); }
    catch(Pass::BADPASS &e) {
        std::map<int , Client*>::iterator user = clients.find(client.getFd());
        if (user != clients.end())
        {
            delete user->second;
            clients.erase(user);
        }
        throw;
    } catch (std::exception &e) {throw;}
    if (!client.getPassword().empty() && !client.getNickname().empty()) {
        std::string msg = ":localhost 001 " + client.getNickname() + " : Welcome to the IRC server : " + client.getNickname() + "!\r\n";
        send(client.getFd(), msg.c_str(), msg.size(), 0);
        client.setlogedin();
        std::cout << YELLOW << client.getNickname() << " logedin successfuly!" << RESET << std::endl;
    }
}

void Server::recive_data(int fd) {
    char buff[500] = {0};
    ssize_t bytes = recv(fd, buff, sizeof(buff), 0);
    if (bytes <= 0) {
        close(fd);
        clients.erase(clients.find(fd));
        return ;
    }
    
    std::map<int, Client*>::iterator user = clients.find(fd);
    if (bytes > 0 && user != clients.end()) {
        std::string data = buff;
        if (!user->second->islogedin())
            try { auth(data, *user->second); } catch (std::exception &e) { std::cout << RED << e.what() << RESET << std::endl;}
        else
            std::cout << user->second->getNickname() << ": " << data;
    } 
}

void Server::_event(sockaddr *a, socklen_t len) {
    for (size_t index = 0; index < c_fds.size(); index++) {
        if ((c_fds[index].revents & POLLIN) == POLLIN) {
            if (c_fds[index].fd == this->server_fd)
                new_client(a, len, c_fds[index].fd);
            else
                recive_data(c_fds[index].fd);
        }
    }
}

void Server::start_server() {
    
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_fd == -1)
        throw std::logic_error("Error: cannot create a socket!");

    // struct addrinfo a;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int reuse = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (bind(this->server_fd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1)
        throw std::logic_error("Error: cannot bind socket to the give port!");
    
    if (listen(this->server_fd, 1) == -1)
        throw std::exception();

    std::cout << GREEN<< "Server listening on port " << port << "..." << RESET << std::endl;
    
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    add_fd(server_fd);
    
    while (true) {
        if (poll(&c_fds[0], c_fds.size(), -1) > 0) {
            _event(reinterpret_cast<struct sockaddr*>(&client_addr), len);
        }
    }
    close(server_fd);
}

Server::~Server(){}