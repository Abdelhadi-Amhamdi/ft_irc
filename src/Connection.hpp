/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/27 19:44:51 by nmaazouz         ###   ########.fr       */
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

