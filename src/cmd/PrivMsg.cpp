/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:01 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/17 14:14:58 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivMsg.hpp"
#include "../Server.hpp"

PrivMsg::PrivMsg(){}

void PrivMsg::exec(std::string &user_infos,std::string &cmd_params, Client &client, Server &server) const  {
    (void)user_infos;
    std::string channel,message;
    std::stringstream ss(cmd_params);
    ss >> channel;
    if (!channel.empty() && channel[0] == '#')
        channel.erase(channel.begin());
    std::string a;
    ss >> message;
    while (ss >> a)
    {
        message += " "; 
        message += a;
    }
    if (!message.empty() && message[0] == ':')
        message.erase(message.begin());
    server.broadcastMessage(channel, message, client.getNickname());
}

PrivMsg::~PrivMsg(){}