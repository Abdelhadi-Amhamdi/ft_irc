/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:44:01 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/25 21:42:07 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivMsg.hpp"

PrivMsg::PrivMsg() : ACommand("PrivMsg") {}

bool PrivMsg::commandArgsChecker(const int &fd) {
    if (!params.size()) {
        sendResponse(":server_name 411 nick :No recipient given (PRIVMSG)\r\n", fd);
        return (false);
    }
    targets = params[0];
    if (params.size() == 1) {
        sendResponse(":server_name 412 nick :No text to send\r\n", fd);
        return (false); 
    }
    message += params[1];
    for (size_t i = 2; i < params.size(); i++)
    {
        message += " ";
        message += params[i];
    }
    if (!message.empty() && message[0] == ':') {
        message.erase(message.begin());
    }
    return (true);
}

void PrivMsg::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    if (!commandArgsChecker(user.getFd()))
        return ;
    ChannelSource *channels_manager = server.getChannelManager();
    ClientSource *clients_manager = server.getClientManager();
    
    std::stringstream targetsStream(targets);
    while (std::getline(targetsStream, target, ','))
    {
        if (!target.empty() && target[0] == '#')
        {
            target.erase(target.begin());
            Channel *channel = channels_manager->getChannelByName(target);
            if (channel) {
                if (channel->isMemberInChannel(user.getFd())) {
                   channel->brodCastMessage(message, user.getNickname());    
                } else {
                    sendResponse(":server_name 404 nick #" + target + " :Cannot send to channel\r\n", user.getFd());
                }
            } else {
                sendResponse(":server_name 401 nick :No such nick/channel\r\n", user.getFd());
            }
        } 
        else
        {
            Client *client = clients_manager->getClientByNickname(target);
            if (client) {
                sendResponse(":" + user.getNickname() + " PRIVMSG " + user.getNickname() + ":" + message + "\r\n", client->getFd());
                sendResponse(":" + user.getNickname() + " PRIVMSG " + client->getNickname() + ":" + message + "\r\n", user.getFd());
            } else {
                sendResponse(":server_name 401 nick :No such nick/channel\r\n", user.getFd());
            }
        }    
    }
    message.clear();
    targets.clear();
    target.clear();
}

PrivMsg::~PrivMsg(){}