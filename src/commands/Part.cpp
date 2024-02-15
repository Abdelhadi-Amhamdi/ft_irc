/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:27:49 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/14 21:29:34 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

Part::Part() : ACommand("Part") {}

void Part::getReason(std::string &buffer) {
    reason.clear();
    if (params.size() > 1){
        reason = get_message(buffer, params[1]);
        if (!reason.empty() && reason[0] != ':')
            reason.insert(reason.begin(), ':');    
    }
}

void Part::Execute(std::string &buffer, Connection &user, Server &server) {
    ChannelSource &channel_manager = server.getChannelManager();
    ClientSource &clients_manager = server.getClientManager();
    executer = clients_manager.getClientByNickname(user.getNickname());
    if (!executer)
        return ;
    commandFormater(buffer);
    if (!params.size()) {
        throw sendResponse(ERR_NEEDMOREPARAMS(executer->getNickname(), this->name), user.getFd());
    }
    std::string channel_name;
    std::stringstream channelsStream(params[0]);
    getReason(buffer);
    while (std::getline(channelsStream, channel_name, ','))
    {
        if (!channel_name.empty() && channel_name[0] == '#')
            channel_name.erase(channel_name.begin());
        else {
            sendResponse(ERR_NOSUCHCHANNEL(executer->getNickname(), channel_name), user.getFd());
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
            channel->delAdmin(user.getFd());
            executer->deletefromgroupsin(channel_name);
        } else {
            sendResponse(ERR_NOSUCHCHANNEL(executer->getNickname(), channel_name), user.getFd());
            continue;
        }
        if (channel && !channel->getMembersCount()) {
            channel_manager.deleteChannel(channel_name);
        }
    }
    params.clear();
}

Part::~Part(){}