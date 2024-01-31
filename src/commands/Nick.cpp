/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/31 09:47:20 by kben-ham         ###   ########.fr       */
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
    if (!params.size()  || (params.size() && params[0].size() == 1 && params[0][0] == ':'))
        throw sendResponse(ERR_NONICKNAME(std::string("nick")), user.getFd());
    if (!isValidNickname(params[0]))
        throw sendResponse(ERR_ERRONNICK(std::string("nick")), user.getFd());
    Client *client = client_manager.getClientByNickname(params[0]);
    if (user.getNickname().empty())
    {
        if (!client) {
            user.setNickname(params[0]);
            client_manager.createClient(user.getFd(), user.getNickname(), user.getHostname());
        } 
        else
            throw sendResponse(ERR_ALREADYINUSE(std::string("nick")), user.getFd());
    }
    else
    {
        executer = client_manager.getClientByNickname(user.getNickname());
        if (!executer) {
            OUT("no exec");
            return ;
        }
        if (!client || client->getFd() == executer->getFd()) {
            if (params[0] != executer->getNickname()) {
                sendResponse(":" + executer->getNickname() + "!~" + executer->getLogin() + "@" + executer->getHostname() + " NICK :" + params[0] + "\r\n" , user.getFd());
                client_manager.deleteClient(user.getNickname());
                client_manager.createClient(user.getFd(), params[0], user.getHostname());
                user.setNickname(params[0]);
            }
        } else
            throw sendResponse(ERR_ALREADYINUSE(std::string("nick")), user.getFd());
    }
}

Nick::~Nick(){}