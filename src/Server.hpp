/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/09 01:04:07 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>

// sockets manipulation
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// user defined classes
#include "Client.hpp"
#include "Channel.hpp"
#include "color.hpp"

// containers
#include <vector>
#include <poll.h>

// algorithms
#include <algorithm>




class Match {
    int value;
    public:
        Match(int fd) : value(fd) {} 
        bool operator()(const Client &c) const {
            return (c.getFd() == value);
        } 
};

class Server {
    public:
        Server(const std::string &password, const int &port);
        void    start_server();
        void    add_fd(int fd);
        void    recive_data(int fd);
        void    _event(sockaddr *a, socklen_t len);
        void    new_client(sockaddr *a, socklen_t len, int fd);
        void    auth(std::string &data, Client &client);
        ~Server();
    private:
        const   int port;
        const   std::string password;
        struct  pollfd fds[1000];
        int     clients_num;
        int     server_fd;
        std::vector<Client> clients;
        std::vector<Channel*> channels;
};
