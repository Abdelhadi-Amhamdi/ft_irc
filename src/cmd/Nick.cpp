/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:10:00 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 13:51:46 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "../Server.hpp"

Nick::Nick() : ACommand("NICK") {}

void Nick::exec(const std::string &value, Client &client, const Server &server) const {
    std::map<int, Client*> clients = server.getClients();
    std::map<int, Client*>::iterator user = std::find_if(clients.begin(), clients.end(), Match_nickname(value));
    if (user == clients.end())
        client.setNickname(value);
    else {
        std::string error_message = ":server_name 433 nick :Nickname is already in use\r\n";
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
        throw std::logic_error("nickname already exist");
    }
}

Nick::~Nick(){}