/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/11 21:50:17 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "commands/ACommand.hpp"


Connection::Connection(const int &serverSocket)
    : nickname(""), user(""), buffer(""){
    sockaddr    clienAdrr;
    socklen_t   clienAdrrLen = sizeof(clienAdrr);
    connection_fd = accept(serverSocket, (struct sockaddr*)&clienAdrr, &clienAdrrLen);
    if (connection_fd == -1)
        throw std::runtime_error("accept of connection failed.");
    std::cout << "Accepted connection from ";
    hostname = inet_ntoa(reinterpret_cast<struct sockaddr_in*>(&clienAdrr)->sin_addr);
    std::cout << hostname << std::endl;
    if (hostname == "127.0.0.1") {
        char buff[500] = {0};
        gethostname(buff, sizeof(buff)); 
        hostname = buff;
    }
}

Connection::~Connection(){}

void Connection::receiveDataFromConnection()
{
    char buff[1024] = {0};
    ssize_t bytes = recv(connection_fd, buff, sizeof(buff)-1, 0);
    if (bytes < 0)
        return;
    if (bytes == 0) {
        buffer.clear();
        buffer = "QUIT\n";
    }
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

void	Connection::authentificate(t_mapConnectionIterator& command, std::string& cmd, Server& server, std::string& buffer)
{
    if (pass.empty() && cmd != "PASS")
        throw std::logic_error(ERR_NOTREGISTERED);

    if (cmd != "PASS" && cmd != "NICK" && cmd != "USER")
        throw std::logic_error(ERR_NOTREGISTERED);
    
    command->second->Execute(buffer, *this, server);

    if (!pass.empty() && !nickname.empty() && !user.empty())
    {
        isAuthentificated = true;
        ACommand::sendResponse(RPL_WELCOME(this->nickname, "IRC", user, hostname), connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.          ___ ______   _______      _______ _______ ______   __   __ _______ ______  \r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         |   |    _ | |       |    |       |       |    _ | |  | |  |       |    _ |  \r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         |   |   | || |       |____|  _____|    ___|   | || |  |_|  |    ___|   | ||  \r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         |   |   |_||_|       |____| |_____|   |___|   |_||_|       |   |___|   |_||_\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         |   |    __  |      _|    |_____  |    ___|    __  |       |    ___|    __  |\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         |   |   |  | |     |_      _____| |   |___|   |  | ||     ||   |___|   |  | |\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         |___|___|  |_|_______|    |_______|_______|___|  |_| |___| |_______|___|  |_|\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         IRC-SERVER\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         An IRC server acts as a central hub where users connect to exchange messages\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         in real-time. It operates on a client-server model, where clients (users) connect\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         to the server to join chat rooms (channels) or engage in private conversations with\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         other users. The server manages user connections, relays messages, and enforces\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         rules and permissions within the network\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         -------- Devlopment Team ----------------------------------------------\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.                o aamhamdi       </> https://github.com/Abdelhadi-Amhamdi\r\n",connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.                o nmaazouz       </> https://github.com/noreddine1\r\n",connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.                o kben-ham       </> https://github.com/Khawla-ben\r\n",connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.\r\n", connection_fd);
        ACommand::sendResponse(":server_name 001 nick :.         -----------------------------------------------------------------------\r\n", connection_fd);
    }
}


bool    Connection::handleDAta(Server& server)
{
    while (!buffer.empty() && buffer.find("\n") != std::string::npos)
    {
        
        std::string part = buffer.substr(0, buffer.find("\n") + 1);
        try {
            std::string strCmd = wichCommand(part);
            std::map<std::string, ACommand*> commands = server.getCommands();
            t_mapConnectionIterator	command = commands.find(strCmd);
            if (command != commands.end()) 
            {
                if (strCmd == "QUIT")
                {
                    command->second->Execute(part, *this, server);
                    return (false);
                }
                if (isAuthentificated == false)
                {
                    authentificate(command, strCmd, server, part);
                } else 
                    command->second->Execute(part, *this, server);
                
            } else {
                if (strCmd != "PONG") {
                    std::string response = ":server_name 421 nick :" + strCmd + " Unknown command\r\n";
                    send(this->connection_fd, response.c_str(), response.size(), 0);    
                }
            }
            buffer.erase(0, part.size());
        } catch (std::exception& e) {
            buffer.erase(0, part.size());
            ACommand::sendResponse(e.what(), this->getFd());
        }
        catch(...) {
            buffer.erase(0, part.size());
        }
    }
    return true;
}

int     Connection::getFd() const {
    return connection_fd; 
}

const std::string& Connection::getBuffer() const { return buffer; }

const std::string& Connection::getHostname() const {
return hostname;
}
const std::string& Connection::getNickname() const {
    return nickname; 
}
void    Connection::setNickname(const std::string &nickname_, ClientSource& clientSource, std::string &message) {
    std::vector<std::string> channels_temp;
    if (nickname_ == this->nickname)
        return;
    Client*	client = clientSource.getClientByNickname(nickname_);
    if (client)
        throw std::logic_error(ERR_ALREADYINUSE(nickname_));
    if (!this->nickname.empty())
    {
        message = RPL_NICK(this->nickname, nickname_);
        client = clientSource.getClientByNickname(this->nickname);
        if (client)
            channels_temp = client->getgroupsin();
        clientSource.deleteClient(this->nickname);
    }
    clientSource.createClient(this, nickname_);
    client = clientSource.getClientByNickname(nickname_);
    if (client)
        const_cast<std::vector<std::string>&>(client->getgroupsin()) = channels_temp;
    nickname = nickname_;
}
const std::string& Connection::getPass() const { return pass; }
void Connection::setPass(const std::string &pass_) { pass = pass_; }
const std::string& Connection::getUser() const { return user; }
void Connection::setUser(const std::string &user_) { user = user_; }
bool Connection::getIsAuthentificated() const { return isAuthentificated; }
