/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:45:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 21:58:58 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : ACommand("User") {}

void User::Execute(std::string &buffer, Connection &user, Server &server) {
    ClientSource *clients_manager = server.getClientManager();
    Client *client = clients_manager->getClientByNickname(user.getNickname());
    if (client && !client->isRegistred())
    {
        std::string prefix = ":localhost 001 " + user.getNickname() + " :";
        commandFormater(buffer);
        userInfosChecker();
        client->setLogin(params[0]);
        client->setHostname(params[1]);
        client->setRealName(params[3]);
        client->setIsRegistred();
        std::string a = ":localhost 001 " + user.getNickname() + " :Welcome to the IRC network\r\n";
        sendResponse(a, user.getFd());
        sendResponse(prefix + "   .---------.\r\n" , user.getFd());
        sendResponse(prefix + "   |.-------.|\r\n" , user.getFd());
        sendResponse(prefix + "   ||>run#  ||\r\n" , user.getFd());
        sendResponse(prefix + "   ||       ||\r\n" , user.getFd());
        sendResponse(prefix + "   |\"-------'|etf\r\n" , user.getFd());
        sendResponse(prefix + ".-^---------^-.\r\n" , user.getFd());
        sendResponse(prefix + "| ---~   AMiGA|\r\n" , user.getFd());
        sendResponse(prefix + "\"-------------' .  enjoy ;)\r\n" , user.getFd());
        params.clear();
    } else if (client) {
        sendResponse(":server_name 462 nick: You may not register!\r\n", user.getFd());
    }
}

User::~User(){}