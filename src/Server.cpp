/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:47:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/29 17:54:20 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "commands/Mode.hpp"


const std::string& Server::getPassword() const {
	return (this->password);
}

const std::unordered_map<std::string, ACommand*> & Server::getCommands() const {
	return (commands);
}

ClientSource &Server::getClientManager() {
	return (clients_manager);
}

ChannelSource &Server::getChannelManager() {
	return (channels_manager);
}

int Server::getFd() const {
	return server_fd;
}

void Server::addConnectionFd(const int &connection_fd) {
	struct pollfd new_fd;
	fcntl(connection_fd, F_SETFL, O_NONBLOCK);
	new_fd.fd = connection_fd;
	new_fd.events = POLLIN;
	connection_fds.push_back(new_fd);
}


void Server::deleteConnectionFd(const int &connection_fd) {
	std::vector<struct pollfd>::iterator it = connection_fds.begin();
	std::vector<struct pollfd>::iterator ite = connection_fds.end();
	for(std::vector<struct pollfd>::iterator t = it; t != ite; t++)
	{
		if (t->fd == connection_fd)
		{
			connection_fds.erase(t);
			break;
		}
	}
}

void Server::deleteConnection(const int &connection_fd) {
	std::unordered_map<int, Connection*>::iterator it = connections.find(connection_fd);
	if (it != connections.end())
        connections.erase(it);
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
	: index(1), port(port), password(password) {
	inializeServer();
	addConnectionFd(this->server_fd);
	commands["PASS"] = new Pass();
	commands["NICK"] = new Nick();
	commands["TOPIC"] = new Topic();
	commands["USER"] = new User();
	commands["JOIN"] = new Join();
	commands["QUIT"] = new Quit();
	commands["MODE"] = new Mode(*this);
	commands["PRIVMSG"] = new PrivMsg();
	commands["PART"] = new Part();
	commands["KICK"] = new Kick();
	commands["INVITE"] = new Invite();
	commands["BOT"] = new Bot();
}

void Server::start_server() {
	try
	{
		while (index != 0) {
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

	int reuse = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
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

Server::~Server()
{
	for (size_t i = 0; i < connection_fds.size(); i++) {
		close(connection_fds[i].fd);
	}
	connection_fds.clear();
	std::unordered_map<std::string, ACommand*>::iterator it = commands.begin();
	for (; it != commands.end(); it++) {
		delete it->second;
	}
	commands.clear();
	std::unordered_map<int, Connection*>::iterator itc = connections.begin();
	for (; itc != connections.end(); itc++) {
		delete itc->second;
	}
	connections.end();
}
