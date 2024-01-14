/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:50 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 11:33:18 by aamhamdi         ###   ########.fr       */
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

// containers
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
	public:
		Server(const std::string &password, const int &port);
		bool	nickNameused(const std::string &name);
		void    start_server();
		void    add_fd(int fd);
		void    recive_data(int fd);
		void    _event(sockaddr *a, socklen_t len);
		void    new_client(sockaddr *a, socklen_t len, int fd);
		void    auth(std::string &data, Client &client);
		const std::string& getPassword() const;
		~Server();
	private:
		int     port;
		int     server_fd;
		const   std::string password;
		std::vector<struct pollfd>  c_fds;
		ClientSource cl_manager;
		ChannelSource ch_manager;
};
