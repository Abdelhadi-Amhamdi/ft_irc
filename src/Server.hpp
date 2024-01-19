/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 15:48:07 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <unistd.h>
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
#include "Connection.hpp"

// STL 
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <map>


class Connection;

class Server {
	private:
		int		server_fd;
		const	int port;
		const	std::string password;
		std::vector<struct pollfd>				connection_fds;
		std::unordered_map<int, Client*>		clients;
		std::unordered_map<int, Connection*>	connections;
	public:
		Server(const std::string &password, const int &port);
		~Server();
		// server geters
		const std::string& getPassword() const;
		// server main functions
		void    inializeServer();
		void    eventsHandler();
		void    start_server();
		void    addConnectionFd(const int &connection_fd); 
};
