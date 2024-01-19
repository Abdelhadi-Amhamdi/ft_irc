/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:47:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 11:15:11 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Connection.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <sys/_types/_size_t.h>
#include <sys/poll.h>
#include <unordered_map>


void Server::_event() {
	for (size_t index = 1; index < c_fds.size(); index++) {
		if ((c_fds[index].revents & POLLIN) == POLLIN) {
			Connection&	currenConnection = connections[c_fds[index].fd];
			currenConnection.receiveData();
			currenConnection.handleDAta(*this);
		}
	}
}

Server::~Server(){}


struct pollfd   getPollfd(int fd)
{
	struct pollfd pollFd;
	pollFd.fd = fd;
	pollFd.events = POLLIN;

	return pollFd;
}

Server::Server(const std::string &password, const int &port) 
	: port(port), password(password) {
		
    inializeServer();
	this->c_fds.push_back(getPollfd(this->server_fd));
    commands["PASS"] = new Pass();  
    commands["NICK"] = new Nick();      
    commands["USER"] = new User();
    commands["JOIN"] = new Join();      
    commands["PRIVMSG"] = new PrivMsg();
}

void Server::add_fd(int fd) {
    struct pollfd a;
    a.fd = fd;
    a.events = POLLIN;
    c_fds.push_back(a);
}

bool Server::nickNameused(const std::string &name) {
    return (cl_manager.checkNickName(name));
}

void	Server::addUserToChannel(const std::string &channel, const std::string &password, int user_fd, std::string user){
    ch_manager.addUserToChannel(channel, password, user_fd, user);
}


void Server::start_server()
{
	    try
    {
        while (true) {
            if (poll(&this->c_fds[0], this->c_fds.size(), -1) == -1)
            {
                std::cerr << "Error on poll.\n";
                continue; 
            }

            //if something hapened the mainSockete, then is connection.
            if (this->c_fds[0].revents & POLLIN)
            {
				try{
					Connection	newConnection(server_fd);
					connections[newConnection.getFd()] = newConnection;
					c_fds.push_back(getPollfd(newConnection.getFd()));
				}
                catch (std::exception& e)
				{
					std::cerr << e.what() << std::endl;
					continue;
				}
            }
            _event();
        }
    } catch (std::exception& e)
    {
        std::cerr << "Exception in startServer: " << e.what() << std::endl;
    }
}

const std::string& Server::getPassword() const {
    return password;
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

    std::cout << "Server started on port " << port << std::endl;
}
