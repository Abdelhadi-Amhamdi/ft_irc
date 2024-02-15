/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:37:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/15 00:51:50 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"

Kick::Kick() : ACommand("Kick") {}

void Kick::getComment(std::string &buffer) {
    comment.clear();
    if (params.size() > 2)
        comment = get_message(buffer, params[2]);
    if (!comment.empty() && comment[0] == ':')
        comment.insert(comment.begin(), ':');
    if (comment[0] == ':')
		comment.erase(comment.begin());
}

void Kick::Execute(std::string &buffer, Connection &user, Server &server) {
    ChannelSource &channels_manager = server.getChannelManager();
    ClientSource &clients_mananger = server.getClientManager();
    executer = clients_mananger.getClientByNickname(user.getNickname());
    if (!executer)
        return;
    commandFormater(buffer);
    if (params.size() < 2) {
        throw sendResponse(ERR_NEEDMOREPARAMS(user.getNickname(), this->name), user.getFd());
    }
    std::string channel_name,users;
    channel_name = params[0];
    users = params[1];
    getComment(buffer);
    if (channel_name[0] == '#')
        channel_name.erase(channel_name.begin());
    else {
        throw sendResponse(ERR_NOSUCHCHANNEL(executer->getNickname(), channel_name), user.getFd());
    }
    Channel *channel = channels_manager.getChannelByName(channel_name);
    if (channel) 
    {
        if (!channel->isMemberInChannel(user.getFd())) {
            throw sendResponse(ERR_NOTONCHANNELL(executer->getNickname(), channel_name), user.getFd());
        }
        if (!channel->checkIfAdmin(user.getFd())) {
            throw sendResponse(ERR_NOTCHANOPER(executer->getNickname(), channel_name), user.getFd());
        }
        std::stringstream ss(users);
        std::string username;
        while (std::getline(ss, username, ','))
        {
            Client *client = clients_mananger.getClientByNickname(username);
            if (client) 
            {
                if (!channel->isMemberInChannel(client->getFd())) {
                    sendResponse(ERR_USERNOTONCHANNEL(executer->getNickname(), username, channel_name), user.getFd());
                    continue;
                }
                channel->broadCastResponse(":" + user.getNickname() + "!~" + executer->getLogin() + "@" + executer->getHostname() + " Kick #" + channel_name + " " + username + " " + comment + "\r\n");
                channel->delUserFromChannel(client->getFd());
                channel->delAdmin(client->getFd());
                executer->deletefromgroupsin(channel_name);
                channel->broadCastResponse(channel->generateMemebrsList(user.getNickname()));
                channel->broadCastResponse(RPL_NAMESEND(executer->getNickname(), channel_name));
            } 
            else 
            {
                sendResponse(ERR_NOSUCHNICK(executer->getNickname(), username), user.getFd());
                continue;
            }
        }
    } 
    else {
        throw sendResponse(ERR_NOSUCHCHANNEL(executer->getNickname(), channel_name), user.getFd());
    }
}

Kick::~Kick(){}
