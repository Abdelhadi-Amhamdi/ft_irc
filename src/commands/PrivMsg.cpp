/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:44:01 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/22 10:19:59 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivMsg.hpp"

PrivMsg::PrivMsg() : ACommand("PrivMsg") {}

void PrivMsg::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    ChannelSource *channels_manager = server.getChannelManager();
    if (!params.size()) {
        sendResponse(":server_name\r\n", user.getFd());
    }
    channel_name = params[0];
    if (!channel_name.empty() && channel_name[0] == '#') {
       channel_name.erase(channel_name.begin());    
    }
    for (size_t i = 1; i < params.size(); i++)
    {
        message += params[i];
        message += " ";
    }
    if (!message.empty() && message[0] == ':') {
        message.erase(message.begin());
    }
    Channel *ch = channels_manager->getChannelByName(channel_name);
    if (ch) {
        ch->brodCastMessage(message, user.getNickname());
    }
    params.clear();
    message.clear();
    channel_name.clear();
}

PrivMsg::~PrivMsg(){}