/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:47:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/18 21:06:10 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const std::string &password, const int &port) 
    : port(port), password(password) {
    commands["PASS"] = new Pass();  
    commands["NICK"] = new Nick();      
    commands["USER"] = new User();
    commands["JOIN"] = new Join();      
    commands["PRIVMSG"] = new PrivMsg();
}

void Server::add_fd(int fd) {
    struct pollfd a;
    a.fd = fd;
    a.events = POLLIN;
    c_fds.push_back(a);
}

bool Server::nickNameused(const std::string &name) {
    return (cl_manager.checkNickName(name));
}

void	Server::addUserToChannel(const std::string &channel, const std::string &password, int user_fd, std::string user){
    ch_manager.addUserToChannel(channel, password, user_fd, user);
}

const std::string& Server::getPassword() const {
    return (this->password);
}

void Server::new_client(sockaddr *a, socklen_t len, int fd) {
    int client_fd = accept(fd, a, &len);
    if (client_fd == -1)
        throw std::exception();
    std::string hostname = inet_ntoa(reinterpret_cast<struct sockaddr_in*>(a)->sin_addr);
    std::cout << BLUE << "Accepted connection from " << hostname << RESET << std::endl;
    add_fd(client_fd);
    cl_manager.createClient(client_fd, hostname);
}

void Server::executer(const std::string &data, Client &client) {
    std::string info,cmd,params,elm;
    std::stringstream ss(data);
    
    if (data[0] == ':')
        ss >> info;
    ss >> cmd;
    while (ss >> elm)
        params += elm + " ";
    if (params[params.size() - 1] == ' ')
        params.erase(params.end() - 1);
    std::map<std::string, ACommand*>::iterator it = commands.find(cmd);
    if (it != commands.end()) {
        try {
            it->second->exec(info, params, client, *this);
        } catch (...) {}
    }
    else
        std::cout << data << std::endl;
}

void Server::recive_data(int fd) {
    char buff[500] = {0};
    ssize_t bytes = recv(fd, buff, sizeof(buff), 0);
    if (bytes <= 0) {
        close(fd);
        cl_manager.deleteClient(fd);
        return ;
    }
    
    Client* user = cl_manager.getClient(fd);
    if (bytes > 0 && user ) {
       // std::cout << bytes << std::endl;
        executer(buff, *user);
        if (!user->islogedin() && !user->getPassword().empty() && !user->getNickname().empty()) {
            user->setlogedin();
            std::string message = ":localhost 001 " + user->getNickname() + " : Welcome to the IRC server : " + user->getNickname() + "!\r\n";
            send(user->getFd(), message.c_str(), message.size(), 0);
            std::cout << YELLOW << user->getNickname() << " logedin successfuly!" << RESET << std::endl;
        }
    } 
}

void Server::broadcastMessage(const std::string &channel_name, const std::string &message, std::string user) {
    ch_manager.broadcastMeassges(channel_name, message, user);
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

    std::cout << GREEN << "Server listening on port " << port << "..." << RESET << std::endl;
    
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    add_fd(server_fd);
    
    while (true) {
        if (poll(&c_fds[0], c_fds.size(), -1) > 0)
            _event(reinterpret_cast<struct sockaddr*>(&client_addr), len);
    }
    close(server_fd);
}

Server::~Server(){}