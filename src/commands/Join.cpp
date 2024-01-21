/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:23:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 20:13:35 by kben-ham         ###   ########.fr       */
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
    if (!params.size()) {
        sendResponse(":server_name 461 nick JOIN :Not enough parameters\r\n", user.getFd());
        return ;
    }
    channels_formater();
    for (size_t i = 0; i < channels.size(); i++) {
        channels_manager->addUserToChannel(channels[i].first, channels[i].second, user.getFd(), user.getNickname());
        // Channel *ch = channels_manager->getChannelByName(channels[i].first);
        // if (!ch) {
        //     channels_manager->createChannel(channels[i].first, channels[i].second);
        //     channels_manager->addUserToChannel(user.getFd(), user.getNickname(), channels[i].first);
        // } else {
        //     if (ch->getKey() == channels[i].second) {
        //         ch->add_user(user.getFd(), user.getNickname(), channels[i].first);
        //     } else {
        //         sendResponse(":server_name 475 nick " + channels[i].first + ":Cannot join channel (+k)\r\n", user.getFd());
        //     }
        // }
    }
    channels.clear();
    params.clear();
}

Join::~Join(){}