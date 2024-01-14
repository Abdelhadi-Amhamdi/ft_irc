/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:10:00 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:36:33 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "../Server.hpp"

Nick::Nick()  {}

void Nick::exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &server) const {
    (void)user_infos;
    if (server.nickNameused(cmd_params))
        client.setNickname(cmd_params);
    else {
        std::string error_message = ":server_name 433 nick :Nickname is already in use\r\n";
        send(client.getFd(), error_message.c_str(), error_message.size(), 0);
        throw std::logic_error("nickname already exist");
    }
}

Nick::~Nick(){}