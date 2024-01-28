/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:45:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/28 16:21:00 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : ACommand("User") {}

void User::Execute(std::string &buffer, Connection &user, Server &server) {
    ClientSource *clients_manager = server.getClientManager();
    Client *client = clients_manager->getClientByNickname(user.getNickname());
    if (client && !client->isRegistred())
    {
        commandFormater(buffer);
        if (params.size() < 4) {
            throw sendResponse(ERR_NEEDMOREPARAMSS(client->getNickname(), this->name), user.getFd());
        }
        client->setLogin(params[0]);
        user_name = params[3];
        for (size_t i = 4; i < params.size(); i++)
            user_name += " " + params[i];
        if (user_name[0] == ':')
            user_name.erase(user_name.begin());
        client->setRealName(user_name);
        client->setIsRegistred();
        sendResponse(":server_name 001 " +  user.getNickname() + " :Welcome to the IRC network : " + user.getNickname() + "!" + user.getNickname() + "@" + client->getHostname() + "\r\n", user.getFd());
        user_name.clear();
    } else if (client) {
        sendResponse(ERR_ALREADYREGISTRED(client->getNickname()), user.getFd());
    }
}

User::~User(){}