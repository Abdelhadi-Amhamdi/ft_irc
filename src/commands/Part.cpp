/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:27:49 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/29 14:29:26 by aamhamdi         ###   ########.fr       */
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
    ChannelSource &channel_manager = server.getChannelManager();
    ClientSource &clients_manager = server.getClientManager();
    executer = clients_manager.getClientByNickname(user.getNickname());
    commandFormater(buffer);
    if (!params.size()) {
        throw sendResponse(ERR_NEEDMOREPARAMSS(executer->getNickname(), this->name), user.getFd());
    }
    std::string channel_name;
    std::stringstream channelsStream(params[0]);
    getReason();
    while (std::getline(channelsStream, channel_name, ','))
    {
        if (!channel_name.empty() && channel_name[0] == '#')
            channel_name.erase(channel_name.begin());
        else {
            sendResponse(ERR_NOSUCHCHANNELL(executer->getNickname(), channel_name), user.getFd());
            continue; 
        }
        Channel *channel = channel_manager.getChannelByName(channel_name);
        if (channel) {
            if (!channel->isMemberInChannel(user.getFd())) {
                sendResponse(ERR_NOTONCHANNELL(executer->getNickname(), channel_name), user.getFd());
                continue;
            }
            channel->broadCastResponse(":" + user.getNickname() + "!~" + executer->getLogin() + "@" + executer->getHostname() + " Part #" + channel_name + " " + reason + "\r\n");
            channel->delUserFromChannel(user.getFd());
            channel->broadCastResponse(channel->generateMemebrsList());
            channel->broadCastResponse(RPL_NAMESEND(executer->getNickname(), channel_name));
        } else {
            sendResponse(ERR_NOSUCHCHANNELL(executer->getNickname(), channel_name), user.getFd());
            continue;
        }
        if (!channel->getMembersCount()) {
            channel_manager.deleteChannel(channel_name);
        }
    }
    params.clear();
}

Part::~Part(){}