/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 17:59:44 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "Client.hpp"
#include "ClientSource.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include "commands/ACommand.hpp"
#include "commands/Pass.hpp"
#include <exception>
#include <stdexcept>
#include <string>

Connection::Connection(const int &serverSocket)
	: isConnected(false), nickname(""), user(""), buffer(""){
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
	if (bytes == 0)
		buffer = "QUIT\n";
	else
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

void	Connection::authentificate(t_mapConnectionIterator& command, std::string& cmd, Server& server)
{
	if (pass.empty() && cmd != "PASS")
		throw std::logic_error(ERR_NOTREGISTERED);

	if (cmd != "PASS" && cmd != "NICK" && cmd != "USER")
		throw std::logic_error(ERR_NOTREGISTERED);
	
	command->second->Execute(buffer, *this, server);

	if (!pass.empty() && !nickname.empty() && !user.empty())
	{
		isAuthentificated = true;
		ClientSource& clientSource = server.getClientManager();
		clientSource.createClient(this);
		ACommand::sendResponse(RPL_WELCOME(this->nickname, "<networkname>", user, hostname), connection_fd);
	}
}

void    Connection::handleDAta(Server& server) 
{
	if (buffer.find("\n") != std::string::npos)
	{
		try {
			std::cout << connection_fd << ": "<< buffer;
			std::string cmd = wichCommand(buffer);
			std::unordered_map<std::string, ACommand*> commands = server.getCommands();
			t_mapConnectionIterator	command = commands.find(cmd);
			if (command != commands.end()) 
			{
				if (isAuthentificated == false)
					authentificate(command, cmd, server);
				else
					command->second->Execute(buffer, *this, server);
			} else {
				if (cmd != "PONG") {
					std::string response = ":server_name 421 nick :" + cmd + " Unknown command\r\n";
					send(this->connection_fd, response.c_str(), response.size(), 0);    
				}
			}
			buffer.clear();
		} catch (std::exception& e) {
			buffer.clear();
			ACommand::sendResponse(e.what(), this->getFd());
		}
		catch(...)
		{
			buffer.clear();
			ACommand::sendResponse("unknown exception\r\n", this->getFd());
			
		}
	}

}

int     Connection::getFd() const {
	return connection_fd; 
}
bool    Connection::getIsConnected() const {
	return isConnected; 
}
const std::string& Connection::getHostname() const {
return hostname;
}
const std::string& Connection::getNickname() const {
	return nickname; 
}
void    Connection::setNickname(const std::string &nickname_, ClientSource& clientSource) {
	Client*	client = clientSource.getClientByNickname(nickname_);
	if (client)
		throw std::logic_error(ERR_ALREADYINUSE(nickname_));
	if (!this->nickname.empty())
		clientSource.deleteClient(this->nickname);
	clientSource.createClient(this, nickname_);
	nickname = nickname_;
}
void    Connection::setIsConnected(bool isConnected_) {
	isConnected = isConnected_; 
}
