/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/20 11:23:18 by aamhamdi         ###   ########.fr       */
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

const std::string& wichCommand(const std::string& str)
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
    if (buffer.find("\n") != std::string::npos)
    {
        std::string cmd = wichCommand(buffer);
        std::unordered_map<std::string, Command*>::iterator command = commands.find(cmd);
        if (command != commands.end()) 
        {
            if (isConnected == false)
            {
                if (cmd == "PASS")
                    command->second->execute(buffer, *this, server);
            }
            else if (nickname.empty())
            {
                if (cmd == "NICK")
                    command->second->execute(buffer, *this, server);
            } else
                command->second->execute(buffer, *this, server);
        }
        buffer.clear();
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
