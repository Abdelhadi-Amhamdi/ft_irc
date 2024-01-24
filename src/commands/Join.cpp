/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:23:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/24 17:30:39 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join() : ACommand("Join") {}

void Join::channels_formater() {
    std::string channels_list,keys_list;
    channels_list = params[0];
    if (params.size() == 2)
        keys_list = params[1];
    std::stringstream channelsStream(channels_list);
    std::stringstream keysStream(keys_list);
    
    std::string item;
    while (std::getline(channelsStream, item, ','))
    {
        std::string key;
        std::getline(keysStream, key, ',');
        if (!item.empty() && item[0] == '#') {
            item.erase(item.begin());
        }
        std::pair<std::string, std::string> elm = std::make_pair(item, key);
        channels.push_back(elm);
    }
}

void Join::Execute(std::string &buffer, Connection &user, Server &server) {
    ChannelSource *channels_manager = server.getChannelManager();
    commandFormater(buffer);
    userInfosChecker();
    if (!params.size())
    {
        sendResponse(":server_name 461 nick JOIN :Not enough parameters\r\n", user.getFd());
        return ;
    }
    ClientSource *client_manager = server.getClientManager();
    Client *tmp = client_manager->getClientByNickname(user.getNickname());
    channels_formater();
    for (size_t i = 0; i < channels.size(); i++) {
        Channel *ch = channels_manager->getChannelByName(channels[i].first);
        if (!ch)
        {
            channels_manager->createChannel(channels[i].first, channels[i].second);
            Channel *channel = channels_manager->getChannelByName(channels[i].first);
            if (channel) {
                channel->addAdmin(user.getFd());
                channel->addUserToChannel(user.getFd(), user.getNickname());
                channel->broadCastResponse(":" + user.getNickname() + " Join #" + channels[i].first + "\r\n");
                channel->broadCastResponse(channel->generateMemebrsList());
                channel->broadCastResponse(":server_name 366 nick " + channels[i].first + " :End of /NAMES list.\r\n");
                tmp->setgroupsin(channels[i].first);
            }
        } else {
            if (ch->getKey() == channels[i].second) {
                ch->addUserToChannel(user.getFd(), user.getNickname());
                ch->broadCastResponse(":" + user.getNickname() + " Join #" + channels[i].first + "\r\n");
                ch->broadCastResponse(ch->generateMemebrsList());
                ch->broadCastResponse(":server_name 366 nick " + channels[i].first + " :End of /NAMES list.\r\n");
                tmp->setgroupsin(channels[i].first);
            } else {
                sendResponse(":server_name 475 nick " + channels[i].first + ":Cannot join channel (+k)\r\n", user.getFd());
            }
        }
    }
    channels.clear();
    params.clear();
}

Join::~Join(){}