/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 15:29:53 by aamhamdi         ###   ########.fr       */
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
#include "color.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Connection.hpp"
#include "ClientSource.hpp"
#include "ChannelSource.hpp"

// commands
#include "commands/ACommand.hpp"
#include "commands/Nick.hpp"
#include "commands/Pass.hpp"
#include "commands/User.hpp"
#include "commands/Join.hpp"

// STL 
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <map>

#define OUT(x) std::cout << x << std::endl;

class Connection;

class Server {
	private:
		int		server_fd;
		const	int port;
		const	std::string password;
		ClientSource	*clients_manager;
		ChannelSource	*channels_manager;
		std::vector<struct pollfd>					connection_fds;
		std::unordered_map<int, Connection*>		connections;
		std::unordered_map<std::string, ACommand*>	commands;
	public:
		Server(const std::string &password, const int &port);
		~Server();
		// server geters
		const std::string&	getPassword() const;
		ClientSource		*getClientManager() const;
		ChannelSource		*getChannelManager() const;
		const std::unordered_map<std::string, ACommand*> & getCommands() const ;
		
		// server main functions
		void    inializeServer();
		void    eventsHandler();
		void    start_server();
		void    addConnectionFd(const int &connection_fd);

		// clients manager methods
		
};
