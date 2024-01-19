/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 11:24:52 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <unistd.h>

// 
#include <sys/types.h>
#include <netdb.h>

// sockets manipulation
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

// user defined classes
#include "Client.hpp"
#include "Channel.hpp"
#include "color.hpp"
#include "ClientSource.hpp"
#include "ChannelSource.hpp"
#include "cmd/Join.hpp"
#include "cmd/PrivMsg.hpp"
#include "cmd/User.hpp"
#include "Connection.hpp"



// containers
#include <unordered_map>
#include <vector>
#include <map>

// algorithms
#include <algorithm>
class Pass;
#include "cmd/Pass.hpp"
#include "cmd/Nick.hpp"

class Match {
	int value;
	public:
		Match(int fd) : value(fd) {} 
		bool operator()(const Client &c) const {
			return (c.getFd() == value);
		} 
};

class Server {
    private:
        const   int port;
        const   std::string password;
        int     server_fd;
        std::vector<struct pollfd> c_fds;
        std::map<int, Client*> clients;
        std::unordered_map<int, Connection> connections;
        std::map<std::string, ACommand*> commands;
		ClientSource cl_manager;
		ChannelSource ch_manager;
    public:
        Server(const std::string &password, const int &port);
        void    start_server();
        void    add_fd(int fd);
        void    recive_data(int fd);
        void    _event(int fd);
        void    new_client(sockaddr *a, socklen_t len, int fd);
        void    auth(std::string &data, Client &client);
        const std::string& getPassword() const;
        const std::map<int, Client*>& getClients() const;

		bool nickNameused(const std::string &name);
		void addUserToChannel(const std::string &channel, const std::string &password, int user_fd, std::string user);
        ~Server();


        void    inializeServer();
        

        bool    acceptConnetion();
        void    _event();
};
