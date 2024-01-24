/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:37:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 22:50:27 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"

Kick::Kick() : ACommand("Kick") {}

void Kick::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    std::string channel_name,username;
    channel_name = params[0];
    username = params[1];
    if (channel_name[0] == '#')
        channel_name.erase(channel_name.begin());
    ChannelSource *channels_manager = server.getChannelManager();
    ClientSource *clients_mananger = server.getClientManager();
    Channel *channel = channels_manager->getChannelByName(channel_name);
    if (channel) 
    {
        if (!channel->checkIfAdmin(user.getFd())) 
        {
            sendResponse(":server_name 482 " + user.getNickname() + " #" + channel_name + " :You're not channel operator\r\n", user.getFd());
            return ;
        }
        Client *client = clients_mananger->getClientByNickname(username);
        if (client) 
        {
            channel->broadCastResponse(":" + user.getNickname() + " Kick #" + channel_name + " " + username + "\r\n");
            channel->delUserFromChannel(client->getFd());
            channel->broadCastResponse(channel->generateMemebrsList());
            channel->broadCastResponse(":server_name 366 nick " + channel_name + " :End of /NAMES list.\r\n");
        } 
        else 
        {
            sendResponse(":server_name 441 nick " + username + " #" + channel_name + " :They aren't on that channel\r\n", user.getFd());
            return ;
        }
    } 
    else 
    {
        sendResponse(":server_name 401 nick "  + channel_name + " :No such nick/channel\r\n", user.getFd());
        return ;
    }
}

Kick::~Kick(){}
