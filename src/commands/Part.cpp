/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:27:49 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/22 13:19:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

Part::Part() : ACommand("Part") {}

void Part::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    ChannelSource *channel_manager = server.getChannelManager();
    std::string channel_name;
    std::stringstream channelsStream(params[0]);
    while (std::getline(channelsStream, channel_name, ','))
    {
        if (!channel_name.empty() && channel_name[0] == '#')
            channel_name.erase(channel_name.begin());
        Channel *channel = channel_manager->getChannelByName(channel_name);
        if (channel) {
            channel->del_user(user.getFd());   
        }
        if (!channel->getMembersCount()) {
            channel_manager->deleteChannel(channel_name);
        }
    }
    params.clear();
}

Part::~Part(){}