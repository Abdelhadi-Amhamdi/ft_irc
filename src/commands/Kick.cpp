/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:37:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/26 16:55:01 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"

Kick::Kick() : ACommand("Kick") {}

void Kick::getComment() {
    comment.clear();
    if (params.size() > 2)
        comment = params[2];
    for (size_t i = 3; i < params.size(); i++)
    {
        comment += " ";
        comment += params[i];
    }
}

void Kick::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    if (params.size() < 2 || params[1] == ":") {
        sendResponse(":server_name 461 nick Part :Not enough parameters\r\n", user.getFd());
        return;
    }
    std::string channel_name,users;
    channel_name = params[0];
    users = params[1];
    getComment();
    if (channel_name[0] == '#')
        channel_name.erase(channel_name.begin());
    else {
        sendResponse(":server_name 403 nick " + channel_name + " :No such channel\r\n", user.getFd());
        return ;
    }
    ChannelSource *channels_manager = server.getChannelManager();
    ClientSource *clients_mananger = server.getClientManager();
    Channel *channel = channels_manager->getChannelByName(channel_name);
    if (channel) 
    {
        if (!channel->isMemberInChannel(user.getFd())) {
            sendResponse(":server_name 442 nick #" + channel_name + " :You're not on that channel", user.getFd());
            return ;
        }
        if (!channel->checkIfAdmin(user.getFd())) 
        {
            sendResponse(":server_name 482 " + user.getNickname() + " #" + channel_name + " :You're not channel operator\r\n", user.getFd());
            return ;
        }
        std::stringstream ss(users);
        std::string username;
        while (std::getline(ss, username, ','))
        {
            Client *client = clients_mananger->getClientByNickname(username);
            if (client) 
            {
                channel->broadCastResponse(":" + user.getNickname() + " Kick #" + channel_name + " " + username + " " + comment + "\r\n");
                channel->delUserFromChannel(client->getFd());
                channel->broadCastResponse(channel->generateMemebrsList());
                channel->broadCastResponse(":server_name 366 nick " + channel_name + " :End of /NAMES list.\r\n");
            } 
            else 
            {
                sendResponse(":server_name 441 nick " + username + " #" + channel_name + " :They aren't on that channel\r\n", user.getFd());
                continue;
            }
        }
    } 
    else 
    {
        sendResponse(":server_name 403 nick " + channel_name + " :No such channel\r\n", user.getFd());
        return ;
    }
}

Kick::~Kick(){}
