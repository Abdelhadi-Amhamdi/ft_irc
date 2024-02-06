/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/05 13:56:59 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

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
#include "commands/Topic.hpp"
#include "commands/Pass.hpp"
#include "commands/User.hpp"
#include "commands/Join.hpp"
#include "commands/Quit.hpp"
#include "commands/PrivMsg.hpp"
#include "commands/Part.hpp"
#include "commands/Kick.hpp"
#include "commands/Invite.hpp"


// STL 
#include <algorithm>
#include <map>
#include <vector>
#include <map>

#define OUT(x) std::cout << x << std::endl;


class Connection;

class Server {
	private:
		int									index;
		int									server_fd;
		const int							port;
		const std::string 					password;
		ClientSource						clients_manager;
		ChannelSource						channels_manager;
		std::vector<struct pollfd>			connection_fds;
		std::map<int, Connection*>			connections;
		std::map<std::string, ACommand*>	commands;
	public:
		Server(const std::string &password, const int &port);
		~Server();
		int&	getIndex();
		int		getFd() const ;
		void    inializeServer();
		void    eventsHandler();
		void    start_server();
		void    addConnectionFd(const int &connection_fd);
		void    deleteConnectionFd(const int &connection_fd);
		void    deleteConnection(const int &connection_fd);
		ClientSource							&getClientManager();
		ChannelSource							&getChannelManager();
		std::vector<struct pollfd>&				getconnections();
		const std::string&						getPassword() const;
		const std::map<std::string, ACommand*>&	getCommands() const ;
};
