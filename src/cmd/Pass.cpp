/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:28:06 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 13:09:47 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include "../Server.hpp"

Pass::Pass() : ACommand("PASS") {}

void Pass::exec(const std::string &pass, Client &cl, Server &c) const {
    if (c.getPassword() != pass) {
        std::string msg = ":server_name 464 nick :Password incorrect\r\n"; 
        send(cl.getFd(), msg.c_str(), msg.size(), 0);
        close(cl.getFd());
        throw std::logic_error("client auth failed: bad password");
    } else
        cl.setPassword(pass);
}

Pass::~Pass(){}