/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:23:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/30 19:09:33 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join() : ACommand("Join") {}

void Join::channels_formater() {
    channels.clear();
    std::string channels_list = "",keys_list = "";
    channels_list = params[0];
    if (params.size() == 2)
        keys_list = params[1];
    std::stringstream channelsStream(channels_list);
    std::stringstream keysStream(keys_list);
    
    std::string item;
    while (std::getline(channelsStream, item, ','))
    {
        std::string key = "";
        std::getline(keysStream, key, ',');
        std::pair<std::string, std::string> elm = std::make_pair(item, key);
        channels.push_back(elm);
    }
}

void Join::Execute(std::string &buffer, Connection &user, Server &server) {
    ChannelSource &channels_manager = server.getChannelManager();
    ClientSource &client_manager = server.getClientManager();
    executer = client_manager.getClientByNickname(user.getNickname());
    if (!executer)
        return;
    commandFormater(buffer);
    if (!params.size())
        throw sendResponse(ERR_NEEDMOREPARAMSS(user.getNickname(), this->name), user.getFd());
    channels_formater();
    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i].first[0] == '#') {
           channels[i].first.erase(channels[i].first.begin()); 
        } else {
            sendResponse(ERR_NOSUCHCHANNEL(user.getNickname(), channels[i].first) ,user.getFd());
            continue;
        }
        Channel *ch = channels_manager.getChannelByName(channels[i].first);
        if (!ch)
        {
            channels_manager.createChannel(channels[i].first, channels[i].second);
            Channel *channel = channels_manager.getChannelByName(channels[i].first);
            if (channel) 
            {
                channel->addAdmin(user.getFd());
                channel->addUserToChannel(user.getFd(), user.getNickname());
                channel->broadCastResponse(":" + user.getNickname() +"!~" + executer->getLogin() + "@" + executer->getHostname() + " Join #" + channels[i].first + "\r\n");
                channel->broadCastResponse(channel->generateMemebrsList());
                channel->broadCastResponse(RPL_NAMESEND(executer->getNickname(), channels[i].first));
                executer->setgroupsin(channels[i].first);
            }
        } 
        else
        {
            ChannelMode& mode = ch->getMode();
            if (!ch->isMemberInChannel(user.getFd()))
            { 
                if (mode.getHasLimit() && (size_t)mode.getLimit() <= ch->getMembersCount()) {
                    throw sendResponse(ERR_CHANHASLIMIT(executer->getNickname(), channels[i].first), user.getFd());
                }
                if (mode.getInvitOnly() && !ch->checkIfInvited(user.getFd())) {
                    throw sendResponse(ERR_INVONLYCHANNEL(executer->getNickname(), channels[i].first), user.getFd());
                }
                if (mode.getHasKey() && mode.getKey() != channels[i].second) {
                    throw sendResponse(ERR_BADCHANNELKEY(executer->getNickname(), channels[i].first), user.getFd());
                }
                ch->addUserToChannel(user.getFd(), user.getNickname());
                ch->broadCastResponse(":" + user.getNickname() + "!~" + executer->getLogin() + "@" + executer->getHostname() + " Join #" + channels[i].first + "\r\n");
                ch->broadCastResponse(ch->generateMemebrsList());
                ch->broadCastResponse(RPL_NAMESEND(executer->getNickname(), channels[i].first));
                sendResponse(":server_name 332 nick #" + channels[i].first + " :" + ch->getTopic() + "\r\n" , user.getFd());
                executer->setgroupsin(channels[i].first);
                if (mode.getInvitOnly())
                    ch->delInvite(user.getFd());
            }
        }
    }
}

Join::~Join(){}