/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 15:43:52 by aamhamdi         ###   ########.fr       */
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

void    Connection::handleDAta(Server& server) {
    Command*    cmd = NULL;
    if (buffer.find("\n") != std::string::npos) {
        if (isConnected == false)
            cmd = new Pass(*this);
        if (cmd) {
            cmd->execute(server);
            delete cmd;   
        }
        buffer = "";
    }
}

void    Connection::connecte(Server& sever, std::string& pass) {
    if (pass == sever.getPassword())
    {
        isConnected = true;
        std::cout << connection_fd << " hase connected.\n"; 
    }
    else {
        std::cout << "bad password.\n";
    }
}
