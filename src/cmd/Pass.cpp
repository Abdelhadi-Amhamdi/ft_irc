/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:28:06 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 13:45:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include "../Server.hpp"

Pass::Pass() : ACommand("PASS") {}

void Pass::exec(const std::string &pass, Client &client, const Server &server) const {
    if (client.getPassword() == server.getPassword()) {
        std::string error_message = ":server_name 462 nick :You may not reregister\r\n"; 
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
    }
    else if (server.getPassword() != pass) {
        std::string error_message = ":server_name 464 nick :Password incorrect\r\n"; 
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
        close(client.getFd());
        throw std::logic_error("client auth failed: bad password");
    } else
        client.setPassword(pass);
}

Pass::~Pass(){}