/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:27:49 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/26 16:18:02 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

Part::Part() : ACommand("Part") {}

void Part::getReason() {
    reason.clear();
    if (params.size() >= 2)
        reason = params[1];
    for (size_t i = 2; i < params.size(); i++)
    {
        reason += " ";
        reason += params[i];
    }
}

void Part::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    if (!params.size()) {
        sendResponse(":server_name 461 nick Part :Not enough parameters\r\n", user.getFd());
        return ;
    }
    ChannelSource *channel_manager = server.getChannelManager();
    std::string channel_name;
    std::stringstream channelsStream(params[0]);
    getReason();
    while (std::getline(channelsStream, channel_name, ','))
    {
        if (!channel_name.empty() && channel_name[0] == '#')
            channel_name.erase(channel_name.begin());
        else {
            sendResponse(":server_name 403 nick " + channel_name + " :No such channel\r\n", user.getFd());
            continue; 
        }
        Channel *channel = channel_manager->getChannelByName(channel_name);
        if (channel) {
            if (!channel->isMemberInChannel(user.getFd())) {
                sendResponse(":server_name 442 nick #" + channel_name + " :You're not on that channel\r\n", user.getFd());
                continue;
            }
            channel->broadCastResponse(":" + user.getNickname() + " Part #" + channel_name + " " + reason + "\r\n");
            channel->delUserFromChannel(user.getFd());
            channel->broadCastResponse(channel->generateMemebrsList());
            channel->broadCastResponse(":server_name 366 nick " + channel_name + " :End of /NAMES list.\r\n");
        } else {
            sendResponse(":server_name 403 nick #" + channel_name + " :No such channel\r\n", user.getFd());
            continue;
        }
        if (!channel->getMembersCount()) {
            channel_manager->deleteChannel(channel_name);
        }
    }
    params.clear();
}

Part::~Part(){}