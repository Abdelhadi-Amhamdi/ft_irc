/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:45:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 15:12:21 by aamhamdi         ###   ########.fr       */
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
        userInfosChecker();
        client->setLogin(params[0]);
        client->setHostname(params[1]);
        client->setRealName(params[3]);
        client->setIsRegistred();
        sendResponse(":server_name 001 nick: Welcome to the IRC server!\r\n", user.getFd());
        params.clear();
    } else if (client) {
        sendResponse(":server_name 462 nick: You may not register!\r\n", user.getFd());
    }
}

User::~User(){}