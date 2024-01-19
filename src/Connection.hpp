/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 15:31:46 by aamhamdi         ###   ########.fr       */
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
#include "commands/Command.hpp"
#include "commands/Pass.hpp"

class Server;

class Connection {
	private:
		int         connection_fd;
		bool        isConnected;
		std::string nickname;
		std::string buffer;
	public:
		
		Connection(const int &serverSocket);
		~Connection();

		// connection main methods
		void    receiveDataFromConnection();

		// connection geters and seters
		int     getFd() const { return connection_fd; }
		bool    getIsConnected() const { return isConnected; }
		const std::string getNickname() const { return nickname; }
		
		void    setNickname(const std::string &nickname_) { nickname = nickname_; }
		void    setIsConnected(bool isConnected_) { isConnected = isConnected_; }
		



		void    handleDAta(Server& server);


		void    connecte(Server& sever, std::string& pass);

		const std::string& getBuffer() const { return buffer; }


};

