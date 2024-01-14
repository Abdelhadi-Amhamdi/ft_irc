/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:56:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:37:39 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join() {}

void Join::exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &server) const {
    (void)user_infos;
    std::string channel, password;
    std::stringstream ss(cmd_params);
    
    ss >> channel;
    ss >> password;
    if (cmd_params[0] == '#')
        cmd_params.erase(cmd_params.begin());
    server.addUserToChannel(cmd_params, client.getFd(), client.getNickname()); 
}

Join::~Join(){}