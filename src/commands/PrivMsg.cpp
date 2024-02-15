/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:44:01 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/14 21:29:25 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivMsg.hpp"

PrivMsg::PrivMsg() : ACommand("PrivMsg") {}

void PrivMsg::commandArgsChecker(std::string &buffer, const int &fd) {
    if (!params.size()) {
        throw sendResponse(ERR_NORECIP(executer->getNickname()), fd);
    }
    targets = params[0];
    if (params.size() == 1) {
        throw sendResponse(ERR_NOTEXTTOSEND(executer->getNickname()), fd);
    }
    message = get_message(buffer, params[1]);
    if (!message.empty() && message[0] == ':') {
        message.erase(message.begin());
    }
}

void PrivMsg::Execute(std::string &buffer, Connection &user, Server &server) {
    message.clear();
    targets.clear();
    target.clear();
    ChannelSource &channels_manager = server.getChannelManager();
    ClientSource &clients_manager = server.getClientManager();
    executer = clients_manager.getClientByNickname(user.getNickname());
    if (!executer)
        return;
    commandFormater(buffer);
    commandArgsChecker(buffer, user.getFd());
    std::stringstream targetsStream(targets);
    while (std::getline(targetsStream, target, ','))
    {
        if (!target.empty() && target[0] == '#')
        {
            target.erase(target.begin());
            Channel *channel = channels_manager.getChannelByName(target);
            if (channel)
            {
                if (channel->isMemberInChannel(user.getFd()))
                   channel->brodCastMessage(message, user.getNickname());    
                else
                    sendResponse(ERR_CANNOTSENDTOCHAN(executer->getNickname(), target), user.getFd());
            } else
                sendResponse(ERR_NOSUCHCHANNEL(executer->getNickname(), target), user.getFd());
        } 
        else
        {
            Client *client = clients_manager.getClientByNickname(target);
            if (client)
            {
                Client *cl = clients_manager.getClientByNickname(user.getNickname());
                if (cl)
                    sendResponse(":" + cl->getNickname() + "!~" + cl->getLogin() + "@localhost" + " PRIVMSG " + client->getNickname() + " :" + message + "\r\n", client->getFd());
            } else
                sendResponse(ERR_NOSUCHNICK(executer->getNickname(), target), user.getFd());
        }    
    }
}

PrivMsg::~PrivMsg(){}