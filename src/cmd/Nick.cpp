/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:10:00 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 13:31:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "../Server.hpp"

Nick::Nick() : ACommand("NICK") {}

void Nick::exec(const std::string &value, Client &cl, Server &sr) const {
    (void)sr;
    std::map<int, Client*> cls = sr.getClients();
    std::map<int, Client*>::iterator user = std::find_if(cls.begin(), cls.end(), Match_nickname(value));
    if (user == cls.end())
        cl.setNickname(value);
    else {
        std::string error_message = ":server_name 433 nick :Nickname is already in use\r\n";
        send(cl.getFd(), error_message.c_str(), error_message.size(), 0);
        std::cout << RED << "nickname already exist\n" << RESET;
    }
}

Nick::~Nick(){}