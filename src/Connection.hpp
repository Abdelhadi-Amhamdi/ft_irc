/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/29 17:40:21 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <iostream>

// socket manipulation
#include <sys/socket.h>
#include <type_traits>

// user defined classes
#include "Server.hpp"
#include "commands/ACommand.hpp"
#include "commands/Pass.hpp"

class Server;

class Connection {
	private:
		int         connection_fd;
		bool        isConnected;
		std::string nickname;
		std::string buffer;
		std::string hostname;
	public:
		Connection(const int &serverSocket);
		~Connection();

		// connection main methods
		void    receiveDataFromConnection();

		// connection geters and seters
		int     getFd() const;
		bool    getIsConnected() const;
		std::string getHostname() const;
		const std::string getNickname() const;
		
		void    setNickname(const std::string &nickname_);
		void    setIsConnected(bool isConnected_);
		



		void    handleDAta(Server& server);


		void    connecte(Server& sever, std::string& pass);

		const std::string& getBuffer() const { return buffer; }


};

