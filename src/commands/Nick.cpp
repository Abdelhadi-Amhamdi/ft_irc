/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/29 14:28:59 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

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
    commandFormater(buffer);
    if (params.size() && params[0].size() == 1 && params[0].at(0) == ':') {
        throw sendResponse(ERR_NONICKNAME(std::string("nick")), user.getFd());
    }
    if (!isValidNickname(params[0])) {
        throw sendResponse(ERR_ERRONNICK(std::string("nick")), user.getFd());
    }
    Client *client = client_manager.getClientByNickname(params[0]);
    if (user.getNickname().empty())
    {
        if (!client)
        {
            user.setNickname(params[0]);
            client_manager.createClient(user.getFd(), user.getNickname(), user.getHostname());
        } 
        else {
            throw sendResponse(ERR_ALREADYINUSE(std::string("nick")), user.getFd());
        }
    }
    else
    {
        Client *exe = client_manager.getClientByNickname(user.getNickname());
        if (!client || client->getFd() == exe->getFd())
        {
            client_manager.createClient(user.getFd(), params[0], user.getHostname());
            client_manager.deleteClient(user.getNickname());
            user.setNickname(params[0]);
        } else {
            throw sendResponse(ERR_ALREADYINUSE(std::string("nick")), user.getFd());
        }
    }
    params.clear();
}

Nick::~Nick(){}