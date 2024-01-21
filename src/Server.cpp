/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:47:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 13:12:28 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

const std::string& Server::getPassword() const {
	return (this->password);
}

const std::unordered_map<std::string, ACommand*> & Server::getCommands() const {
	return (commands);
}

ClientSource *Server::getClientManager() const {
	return (clients_manager);
}

ChannelSource *Server::getChannelManager() const {
	return (channels_manager);
}

void Server::addConnectionFd(const int &connection_fd) {
	struct pollfd new_fd;
	new_fd.fd = connection_fd;
	new_fd.events = POLLIN;
	connection_fds.push_back(new_fd);
}

void Server::eventsHandler() {
	for (size_t index = 1; index < connection_fds.size(); index++) {
		if ((connection_fds[index].revents & POLLIN) == POLLIN) {
			Connection *currenConnection = connections[connection_fds[index].fd];
			currenConnection->receiveDataFromConnection();
			currenConnection->handleDAta(*this);
		}
	}
}

Server::Server(const std::string &password, const int &port) 
	: port(port), password(password) {
	clients_manager = new ClientSource();
    channels_manager = new ChannelSource();
	inializeServer();
	addConnectionFd(this->server_fd);
	commands["PASS"] = new Pass();
	commands["NICK"] = new Nick();
	commands["TOPIC"] = new Topic();
}

void Server::start_server() {
	try
	{
		while (true) {
			if (poll(&this->connection_fds[0], this->connection_fds.size(), -1) == -1)
			{
				std::cerr << "Error on poll.\n";
				continue; 
			}
			if (this->connection_fds[0].revents & POLLIN)
			{
				try {
					Connection	*newConnection = new Connection(server_fd);
					connections[newConnection->getFd()] = newConnection;
					addConnectionFd(newConnection->getFd());
				}
				catch (std::exception& e) {
					std::cerr << e.what() << std::endl;
				}
			}
			eventsHandler();
		}
	} catch (std::exception& e) {
		std::cerr << "Exception in startServer: " << e.what() << std::endl;
	}
}

void    Server::inializeServer() {
	this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_fd == -1)
		throw std::runtime_error("Creation socket failed.");

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->server_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
	{
		close(this->server_fd);
		throw std::runtime_error("Error in binding.");
	}
	if (listen(this->server_fd, SOMAXCONN) == -1)
	{
		close(this->server_fd);
		throw std::runtime_error("Error listening for connections.");
	}
	std::cout << GREEN << "Server started listening on port " << port << RESET << std::endl;
}

Server::~Server() {}
