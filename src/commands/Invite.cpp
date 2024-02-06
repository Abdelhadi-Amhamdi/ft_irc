/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:47:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 14:43:18 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

Invite::Invite() : ACommand("Invite") {}

void Invite::Execute(std::string &buffer, Connection &user, Server &server) {
    ClientSource &clients_manager = server.getClientManager();
    ChannelSource &channels_manager = server.getChannelManager();
    executer = clients_manager.getClientByNickname(user.getNickname());
    if (!executer)
        return;
    commandFormater(buffer);
    if (params.size() < 2) {
        throw (sendResponse(ERR_NEEDMOREPARAMS(user.getNickname(), "INVITE") , user.getFd()));
    }
    std::string nickname,channel_name;
    nickname = params[0];
    channel_name = params[1];
    if (channel_name[0] == '#')
        channel_name.erase(channel_name.begin());
    else
        throw (sendResponse(ERR_NOSUCHCHANNEL(user.getNickname(), "INVITE"), user.getFd()));
    
    Channel *channel = channels_manager.getChannelByName(channel_name);
    if (channel && !channel->isMemberInChannel(user.getFd())) {
        throw (sendResponse(ERR_NOTONCHANNELL(user.getNickname(), channel_name), user.getFd()));
    }
    if (channel && !channel->checkIfAdmin(user.getFd())) {
        throw (sendResponse(ERR_CHANOPRIVSNEEDED(user.getNickname(), "INVITE"), user.getFd()));
    }
    Client *client = clients_manager.getClientByNickname(nickname);
    if (client)
    {
        if (channel)
        {
            if (channel->isMemberInChannel(client->getFd())) {
                throw (sendResponse(ERR_ALREADYONCHANNEL(user.getNickname(), channel_name), user.getFd()));
            }
            if (channel->getMode().getHasLimit() == true)
                channel->addInvite(client->getFd());
            sendResponse(":" + user.getNickname() + "!~" + client->getLogin() + "@" + client->getHostname() + " Invite " + client->getNickname() + " #" + channel->getName() + "\r\n", client->getFd());
            sendResponse(RPL_INVITING(user.getNickname(), client->getNickname(), channel->getName()), user.getFd());
        }
        else {
            throw (sendResponse(ERR_NOSUCHCHANNEL(user.getNickname(), "INVITE"), user.getFd()));
        }
    } 
    else {
        throw (sendResponse(ERR_NOSUCHNICKK(user.getNickname(), "INVITE"), user.getFd()));
    }
}

Invite::~Invite(){}