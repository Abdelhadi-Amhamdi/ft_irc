/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:52 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 15:51:45 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void Bot::sendResponse(const std::string &message) {
    send(bot_fd, message.c_str(), message.size(), 0);
}

in_addr_t getIpAdress(const std::string &hostname, const std::string &port) {
    struct addrinfo hints, *res;
    in_addr_t ret;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((getaddrinfo(hostname.c_str(), port.c_str(), &hints, &res)) != 0) {
        std::cerr << "Error: getaddrinfo failed" << std::endl;
        return (-1);
    }
    if (res != NULL) {
        if (res->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = reinterpret_cast<struct sockaddr_in *>(res->ai_addr);
            if (ipv4) {
                ret = ipv4->sin_addr.s_addr;
                freeaddrinfo(res);
                return (ret);
            }
        }
    }
    freeaddrinfo(res);
    return (-1);    
}

void Bot::authentification(const std::string &password) {
    std::string message = "PASS " + password + "\n";
    send(bot_fd, message.c_str(), message.size(), 0);
    usleep(500);
    send(bot_fd, "NICK bot\n", 9, 0);
    usleep(500);
    send(bot_fd, "USER bot 0 * bot\n", 17, 0);
    usleep(500);
}

void Bot::dataHandler(std::string data) {
    params.clear();
    size_t pos = data.find("bot");
    if (pos != std::string::npos)
    {
        std::string nickname = data.substr(1, data.find("!") - 1);
        std::string message = data.substr(pos + 4, data.size() - pos - 4);
        if (!message.empty() && message[0] == ':')
            message.erase(message.begin());
        std::string item;
        std::stringstream ss(message);
        while(ss >> item)
            params.push_back(item);
        if (params.size() > 1 && params[0] == "weather")
            Weather(nickname, params[1]);
        else if (params.size() && params[0] == "help")
            manualHelper(nickname);
        else
            sendResponse("PRIVMSG " + nickname + " :Hey I'm Bot ,How Can I Help You ?\r\n");
    }
}

void Bot::initBotSocket(const int &port) {
    std::string str_port;
    std::stringstream ss("");
    ss << port;
    ss >> str_port;
    bot_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (bot_fd == -1)
        throw std::logic_error("Error: cannot create a socket");
    sockaddr_in botAddr;
    botAddr.sin_family = AF_INET;
    botAddr.sin_port = htons(port);
    botAddr.sin_addr.s_addr = getIpAdress("127.0.0.1", str_port);
    if (connect(bot_fd, (const sockaddr*)(&botAddr), sizeof(botAddr)) == -1)
        throw std::logic_error("Error: cannot connect");
}

Bot::Bot(const int &port, const std::string password)
    :password(password) 
{
    initBotSocket(port);
    fds[0].fd = bot_fd;
    fds[0].events = POLLIN;
    authentification(password);
    manualInit();
}

void Bot::startBot() {
    while (true) {
        if (poll(fds, 1, -1) == -1) {
            std::cerr << "poll failed\n";
            return;
        }
        if (fds[0].revents & POLLIN) { 
            ssize_t bytes = recv(bot_fd, buff, sizeof(buff), 0);
            if (bytes)
            {
                buff[bytes] = '\0';
                std::string data = buff;
                if (data.find("!") == std::string::npos || data.find("PRIVMSG") == std::string::npos || data.find("bot") == std::string::npos)
                    continue;
                dataHandler(data);
            } else if (bytes == 0) {
                close(bot_fd);
                break;
            }  
        }
    }
}

Bot::~Bot(){}