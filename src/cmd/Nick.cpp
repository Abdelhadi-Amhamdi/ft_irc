/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:10:00 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 11:29:23 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "../Server.hpp"

Nick::Nick() : ACommand("NICK") {}

void Nick::exec(const std::string &value, Client &client, Server &server) const {

    if (server.nickNameused(value))
        client.setNickname(value);
    else {
        std::string error_message = ":server_name 433 nick :Nickname is already in use\r\n";
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
        throw std::logic_error("nickname already exist");
    }
}

Nick::~Nick(){}