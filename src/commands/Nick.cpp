/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/15 00:23:26 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include <map>
#include <stdexcept>
#include <string>

Nick::Nick() : ACommand("Nick") {}

bool Nick::isValidNickname(const std::string &nickname) const {
    if (nickname.size() > 9)
        return (false);
    if (nickname.find("#") != std::string::npos)
        return (false);
    if (std::isdigit(nickname[0]) || nickname[0] == ':')
        return (false);
    return (true);
}

void Nick::Execute(std::string &buffer, Connection &user, Server &server) {
    ClientSource &client_manager = server.getClientManager();
    ChannelSource &channel_manager = server.getChannelManager();
    commandFormater(buffer);

    if (params.empty())
        throw std::logic_error(ERR_NONICKNAME(user.getNickname()));
    
    std::string&    nick = params[0];
    std::string     userNickname = user.getNickname();
    if (params.size() > 1 || isValidNickname(nick) == false)
        throw std::logic_error(ERR_ERRONNICK((userNickname.empty() ? "*" : userNickname), nick));
    std::string message;
    user.setNickname(nick, client_manager, message);
    if (!message.empty()) {
        Client *client = client_manager.getClientByNickname(user.getNickname());
        if (client)
        {
            sendResponse(message, user.getFd());
            std::vector<std::string> channels = client->getgroupsin();
            std::vector<std::string>::const_iterator it = channels.begin();
            for (; it != channels.end(); it++)
            {
                Channel *ch = channel_manager.getChannelByName(*it);
                if (ch) {
                    ch->delUserFromChannel(user.getFd());
                    ch->addUserToChannel(user.getFd(), nick);
                    ch->broadCastResponse(message);
                }
            }
        }
    }
}

Nick::~Nick(){}