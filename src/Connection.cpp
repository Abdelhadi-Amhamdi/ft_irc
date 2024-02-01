/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 16:08:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(const int &serverSocket)
	: isConnected(false), buffer("") {
	sockaddr    clienAdrr;
	socklen_t   clienAdrrLen = sizeof(clienAdrr);
	connection_fd = accept(serverSocket, (struct sockaddr*)&clienAdrr, &clienAdrrLen);
	if (connection_fd == -1)
		throw std::runtime_error("accept of connection failed.");
	std::cout << BLUE << "Accepted connection from ";
	hostname = inet_ntoa(reinterpret_cast<struct sockaddr_in*>(&clienAdrr)->sin_addr);
	std::cout << hostname << RESET << std::endl;
}

Connection::~Connection(){}

void Connection::receiveDataFromConnection()
{
	char buff[1024] = {0};
	ssize_t bytes = recv(connection_fd, buff, sizeof(buff), 0);
	if (bytes < 0)
		throw std::runtime_error("Error: in receving of message");
	buffer += buff;
}

const std::string wichCommand(const std::string& str)
{
	std::string res;
	std::stringstream strStream(str);
	strStream >> res;
	if (!res.empty() && res[0] == ':')
		strStream >> res;
	return (res);
}

void    Connection::handleDAta(Server& server) 
{
	if (!buffer.empty() && buffer.find("\n") != std::string::npos)
	{
		std::string cmd = wichCommand(buffer);
		std::unordered_map<std::string, ACommand*> commands = server.getCommands();
		std::unordered_map<std::string, ACommand*>::iterator command = commands.find(cmd);
		if (command != commands.end()) 
		{
			try {
				if (nickname.empty())
				{
					if (cmd == "PASS")
						command->second->Execute(buffer, *this, server);
					else if (cmd == "NICK")
						command->second->Execute(buffer, *this, server);
				} else {
						command->second->Execute(buffer, *this, server);
				}
			} catch (...) {}
		} else {
			if (cmd != "PONG") {
				std::string response = ":server_name 421 nick :" + cmd + " Unknown command\r\n";
				send(this->connection_fd, response.c_str(), response.size(), 0);    
			}
		}
		buffer.clear();
	}

}

int     Connection::getFd() const {
	return connection_fd; 
}
bool    Connection::getIsConnected() const {
	return isConnected; 
}
std::string Connection::getHostname() const {
return hostname;
}
const std::string Connection::getNickname() const {
	return nickname; 
}
void    Connection::setNickname(const std::string &nickname_) {
	nickname = nickname_; 
}
void    Connection::setIsConnected(bool isConnected_) {
	isConnected = isConnected_; 
}
