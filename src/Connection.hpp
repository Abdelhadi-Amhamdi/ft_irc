/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/04 13:23:08 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <iostream>

// socket manipulation
#include <string>
#include <sys/socket.h>
#include <map>

// user defined classes
#include "Server.hpp"
#include "commands/ACommand.hpp"
#include "commands/Pass.hpp"

class Server;
class	ACommand;
class	ClientSource;

typedef std::map<std::string, ACommand*>::iterator t_mapConnectionIterator;

class Connection {
	private:
		int         connection_fd;
		bool		isAuthentificated;
		std::string	pass;
		std::string nickname;
		std::string	user;
		std::string buffer;
		std::string hostname;
		void	authentificate(t_mapConnectionIterator& command, std::string& cmd, Server& server, std::string& buffer);
	public:
		Connection(const int &serverSocket);
		~Connection();
		int		getFd() const;
		void	receiveDataFromConnection();
		void    setNickname(const std::string &nickname_, ClientSource& clientSource);
		void	setPass(const std::string &pass_);
		void	setUser(const std::string &user_);
		bool	getIsConnected() const;
		bool	handleDAta(Server& server);
        bool	getIsAuthentificated() const;
		const std::string&	getBuffer() const;
		const std::string&	getHostname() const;
		const std::string&	getNickname() const;
		const std::string&	getPass() const;
		const std::string&	getUser() const;
};

