/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:47:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/26 06:09:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

Invite::Invite() : ACommand("Invite") {}

void Invite::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    std::string nickname,channel_name;
    if (params.size() != 2) {
        sendResponse(":server_name 461 nick JOIN :Not enough parameters\r\n", user.getFd());
        return ;
    }
    nickname = params[0];
    channel_name = params[1];
    ChannelSource *channels_manager = server.getChannelManager();
    ClientSource *clients_manager = server.getClientManager();
    if (!channel_name.empty() && channel_name[0] == '#')
        channel_name.erase(channel_name.begin());
    
    Channel *channel = channels_manager->getChannelByName(channel_name);
    if (channel && !channel->isMemberInChannel(user.getFd())) {
        sendResponse(":server_name 442 nick #" + channel_name + " :You're not on that channel\r\n", user.getFd());
        return ;   
    }
    if (channel && !channel->checkIfAdmin(user.getFd())) {
        sendResponse(":server_name 442 nick #" + channel_name + " :You're not channel operator\r\n", user.getFd());
        return ;
    }
    Client *client = clients_manager->getClientByNickname(nickname);
    if (client)
    {
        if (channel)
        {
            if (channel->isMemberInChannel(client->getFd())) {
                sendResponse(":sever_name 443 nick #" + channel_name + " :is already on channel\r\n", user.getFd());
                return ;
            }
            channel->addInvite(client->getFd());
            sendResponse(":" + user.getNickname() + " Invite " + client->getNickname() + " #" + channel->getName() + "\r\n", client->getFd());
            sendResponse(":server_name 341 " + user.getNickname() + " " + client->getNickname() + " #" + channel->getName() + "\r\n", user.getFd());
        }
        else {
            sendResponse(":server_name 403 " + client->getNickname() + " #" + channel_name + " :No such channel\r\n", user.getFd());
        }
    } 
    else {
        sendResponse(":server_name 401 nick "  + channel_name + " :No such nick/channel\r\n", user.getFd()); // if not such client   
    }
}

Invite::~Invite(){}