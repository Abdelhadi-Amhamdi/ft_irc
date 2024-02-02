/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:23:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/02 15:54:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join() : ACommand("Join") {}

void Join::channels_formater() {
    channels.clear();
    std::string channels_list = "",keys_list = "";
    channels_list = params[0];
    if (params.size() >= 2)
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


int Join::isValidChannelName(const std::string &channel_name) {
    if (!channel_name.size() || channel_name.size() > 200)
        return (0);
    if (channel_name[0] != '#')
        return (0);
    for (size_t i = 0; i < channel_name.size(); i++)
    {
        if (channel_name[i] == 7)
            return (0);
    }
    return (1);
}

void Join::Execute(std::string &buffer, Connection &user, Server &server) {
    ChannelSource &channels_manager = server.getChannelManager();
    ClientSource &client_manager = server.getClientManager();
    executer = client_manager.getClientByNickname(user.getNickname());
    if (!executer) {
        std::cerr << "nick => |" << user.getNickname() << "| no exec join\n";   
        return ;
    }
    commandFormater(buffer);
    if (!params.size())
        throw sendResponse(ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN"), user.getFd());
    channels_formater();
    std::vector<std::pair<std::string, std::string> >::iterator it = channels.begin();
    for (; it != channels.end(); it++) {
        if (isValidChannelName(it->first)) {
           it->first.erase(it->first.begin());
        } else {
            sendResponse(ERR_NOSUCHCHANNEL(user.getNickname(), it->first) ,user.getFd());
            continue;
        }
        Channel *channel = channels_manager.getChannelByName(it->first);
        if (!channel)
        {
            channels_manager.createChannel(it->first);
            channel = channels_manager.getChannelByName(it->first);
            if (channel) 
            {
                channel->addAdmin(user.getFd());
                channel->addUserToChannel(user.getFd(), user.getNickname());
                channel->broadCastResponse(":" + user.getNickname() +"!~" + executer->getLogin() + "@" + executer->getHostname() + " JOIN #" + it->first + "\r\n");
                channel->broadCastResponse(channel->generateMemebrsList());
                channel->broadCastResponse(RPL_NAMESEND(executer->getNickname(), it->first));
                executer->setgroupsin(it->first);
            }
        } 
        else
        {
            ChannelMode& mode = channel->getMode();
            if (!channel->isMemberInChannel(user.getFd()))
            { 
                if (mode.getHasLimit() && (size_t)mode.getLimit() <= channel->getMembersCount()) {
                    throw sendResponse(ERR_CHANHASLIMIT(executer->getNickname(), it->first), user.getFd());
                }
                if (mode.getInvitOnly() && !channel->checkIfInvited(user.getFd())) {
                    throw sendResponse(ERR_INVONLYCHANNEL(executer->getNickname(), it->first), user.getFd());
                }
                if (mode.getHasKey() && mode.getKey() != it->second) {
                    throw sendResponse(ERR_BADCHANNELKEY(executer->getNickname(), it->first), user.getFd());
                }
                channel->addUserToChannel(user.getFd(), user.getNickname());
                channel->broadCastResponse(":" + user.getNickname() + "!~" + executer->getLogin() + "@" + executer->getHostname() + " JOIN #" + it->first + "\r\n");
                channel->broadCastResponse(channel->generateMemebrsList());
                channel->broadCastResponse(RPL_NAMESEND(executer->getNickname(), it->first));
                sendResponse(":server_name 332 nick #" + it->first + " :" + channel->getTopic() + "\r\n" , user.getFd());
                executer->setgroupsin(it->first);
                channel->delInvite(user.getFd());
            }
        }
    }
}

Join::~Join(){}