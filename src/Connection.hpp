/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 17:47:28 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <iostream>

// socket manipulation
#include <string>
#include <sys/socket.h>
#include <type_traits>
#include <unordered_map>

// user defined classes
#include "Server.hpp"
#include "commands/ACommand.hpp"
#include "commands/Pass.hpp"

class Server;
class	ACommand;
class	ClientSource;

typedef std::unordered_map<std::string, ACommand*>::iterator t_mapConnectionIterator;

class Connection {
	private:
		int         connection_fd;
		bool		isAuthentificated;
		bool        isConnected;
		std::string	pass;
		std::string nickname;
		std::string	user;
		std::string buffer;
		std::string hostname;
		void	authentificate(t_mapConnectionIterator& command, std::string& cmd, Server& server);
	public:
		Connection(const int &serverSocket);
		~Connection();

		// connection main methods
		void    receiveDataFromConnection();

		// connection geters and seters
		// connection geters and seters
		int     getFd() const;
		const std::string& getBuffer() const { return buffer; }
		bool    getIsConnected() const;
		const std::string& getHostname() const;
		
		const std::string& getNickname() const;
		void    setNickname(const std::string &nickname_, ClientSource& clientSource);
		
		const std::string& getPass() const { return pass; }
		void setPass(const std::string &pass_) { pass = pass_; }
		
		const std::string& getUser() const { return user; }
		void setUser(const std::string &user_) { user = user_; }
		
		void    setIsConnected(bool isConnected_);
		void    handleDAta(Server& server);

		void    connecte(Server& sever, std::string& pass);
		bool getIsAuthentificated() const { return isAuthentificated; }


};

