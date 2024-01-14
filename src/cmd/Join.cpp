/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:56:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 11:30:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join(const std::string &name) : ACommand(name) {}

void Join::exec(const std::string &value, Client &client, Server &server) const {
    std::string channel, password;
    std::stringstream ss(value);
    
    ss >> channel;
    ss >> password;

    std::vector<Channel*> channels = server.getChannels();
    
    
}

Join::~Join(){}