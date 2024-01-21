/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 20:06:34 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

Nick::Nick() : ACommand("Nick") {}

void Nick::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    ClientSource *client_manager = server.getClientManager();
    Client *client = client_manager->getClientByNickname(params[0]);
    
    if (user.getNickname().empty())
    {
        if (!client)
        {
            user.setNickname(params[0]);
            client_manager->createClient(user.getFd(), user.getNickname());
        } 
        else {
            sendResponse(":server_name 433 nick :Nickname is already in use\r\n", user.getFd());
        }
    }
    else
    {
        Client *exe = client_manager->getClientByNickname(user.getNickname());
        if (!client || client->getFd() == exe->getFd())
        {
            client_manager->createClient(user.getFd(), params[0]);
            client_manager->deleteClient(user.getNickname());
            user.setNickname(params[0]);
        } else {
            sendResponse(":server_name 433 nick :Nickname is already in use\r\n", user.getFd());
        }
    }
    params.clear();
}

Nick::~Nick(){}