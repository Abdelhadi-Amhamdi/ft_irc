/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:28:06 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:36:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include "../Server.hpp"

Pass::Pass() {}


void Pass::exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &server) const {
    (void)user_infos;
    if (client.getPassword() == server.getPassword()) {
        std::string error_message = ":server_name 462 nick :You may not reregister\r\n"; 
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
    }
    else if (server.getPassword() != cmd_params) {
        std::string error_message = ":server_name 464 nick :Password incorrect\r\n"; 
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
        close(client.getFd());
        throw BADPASS();
    } else
        client.setPassword(cmd_params);
}

Pass::~Pass(){}