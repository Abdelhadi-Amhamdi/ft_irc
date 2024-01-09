/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:47:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/09 01:24:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const std::string &password, const int &port) 
    : port(port), password(password), clients_num(0) {}

void Server::add_fd(int fd) {
    this->fds[this->clients_num].fd = fd;
    this->fds[this->clients_num].events = POLLIN;
    this->clients_num++;
}

void Server::new_client(sockaddr *a, socklen_t len, int fd) {
    int client_fd = accept(fd, a, &len);
    if (client_fd == -1)
        throw std::exception();
    std::cout << BLUE << "Accepted connection from " << inet_ntoa(reinterpret_cast<struct sockaddr_in*>(a)->sin_addr) << RESET << std::endl;
    add_fd(client_fd);
    Client c(client_fd);
    clients.push_back(c);
}

void pass(std::string &password, Client &c, std::string pass) {
    if (password != pass) {
        std::string msg = RED + "Error: inalid password\n" + RESET; 
        send(c.getFd(), msg.c_str(), msg.size(), 0);
    } else
        c.setPassword(password);
}

void nick(std::string &nick, Client &c) {
    // if (c.getNickname().empty()) {
    //     for ()
    // }
    // else
    c.setNickname(nick);
        
}

void Server::auth(std::string &data, Client &client) {
    std::string key, value;
    std::stringstream str(data);
    str >> key;
    str >> value;
    if (key == "PASS" && client.getPassword().empty())
        pass(value, client, this->password);
    else if (key == "NICK")
        nick(value, client);
    else {
        std::string msg = RED + "Error: auth failed, invalid command (PASS, NICK, USER)!\n" + RESET; 
        send(client.getFd(), msg.c_str(), msg.size(), 0);
    }
}

void Server::recive_data(int fd) {
    char buff[500] = {0};
    ssize_t bytes = recv(fd, buff, sizeof(buff), 0);
    
    std::vector<Client>::iterator user = std::find_if(clients.begin(), clients.end(), Match(fd));
    if (bytes > 0 && user != clients.end()) {
        std::string data = buff;
        
        if (!user->islogedin()) {
            std::cout << "client_fd: " << user->getFd() << " - auth : " << data;
            auth(data, *user);
            if (!user->getPassword().empty() && !user->getNickname().empty()) {
                std::string msg = ":localhost 001 " + user->getNickname() + " : Welcome to the IRC server : " + user->getNickname() + "!\r\n";
                send(user->getFd(), msg.c_str(), msg.size(), 0);
                user->setlogedin();
            }
        }
        else {
            std::cout << user->getNickname() << ": " << data;
            // if (data == "join\n" && data.size() == 5)
            //     channels[0]->add_user(user->getFd(), user->getNickname());
            // else if (data.find("join") != std::string::npos) {
            //     Channel *ch = new Channel(user->getFd(), "test", user->getNickname());
            //     channels.push_back(ch);
            //     // std::cout << CYAN << "Create a channel" << RESET << std::endl;
            // } else if (data.find("msg") != std::string::npos) {
            //     channels[0]->brodcast_msg(data);
            // }
        }
    } 
}

void Server::_event(sockaddr *a, socklen_t len) {
    for (int index = 0; index < this->clients_num; index++) {
        if ((this->fds[index].revents & POLLIN) == POLLIN) {
            if (this->fds[index].fd == this->server_fd)
                new_client(a, len, this->fds[index].fd);
            else
                recive_data(this->fds[index].fd);
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

    if (bind(this->server_fd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1)
        throw std::logic_error("Error: cannot bind socket to the give port!");
    
    if (listen(this->server_fd, 1) == -1)
        throw std::exception();

    std::cout << GREEN<< "Server listening on port " << port << RESET << std::endl;
    
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    add_fd(server_fd);
    
    while (true) {
        if (poll(this->fds, this->clients_num, 10000) > 0)
            _event(reinterpret_cast<struct sockaddr*>(&client_addr), len);
    }
}

Server::~Server(){}