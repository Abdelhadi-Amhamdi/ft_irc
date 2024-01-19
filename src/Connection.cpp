#include "Connection.hpp"
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.hpp"
#include "commands/Command.hpp"

#include "commands/Pass.hpp"

Connection::Connection()
    : isConnected(false), buffer("")
{
    
}

Connection::Connection(int serverSocket)
    : isConnected(false)
{
    sockaddr clienAdrr;
	socklen_t   clienAdrrLen = sizeof(clienAdrr);
    fd = accept(serverSocket, (struct sockaddr*)&clienAdrr, &clienAdrrLen);
    if (fd == -1)
        throw std::runtime_error("accept of connection failed.");
}

Connection::~Connection(){}

void Connection::receiveData()
{
    char buff[1024] = {0};
    ssize_t bytes = recv(fd, buff, sizeof(buff), 0);
    if (bytes < 0)
        throw std::runtime_error("Error: in receving of message");
    buffer += buff;
}

void    Connection::handleDAta(Server& server) {
    if (buffer[buffer.size() - 1 == '\n'])
    {
        Command*    cmd = NULL;
        if (isConnected == false)
            cmd = new Pass(*this);
        if (nickname.empty())
        // execute nick command
            
        if (cmd)
            cmd->execute(server);
    }
    buffer = "";
}

void    Connection::connecte(Server& sever, std::string& pass) {
    if (pass == sever.getPassword())
    {
        isConnected = true;
        std::cout << fd << " hase connected.\n"; 
    }
    else {
        std::cout << "bad password.\n";
    }
}
