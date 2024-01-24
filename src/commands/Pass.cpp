/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:52:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/24 21:48:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"


Pass::Pass() : ACommand("PASS") {}

void Pass::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    userInfosChecker();
    if (server.getPassword() != params[0]) {
        sendResponse(":server_name 464 nick :Password incorrect\r\n", user.getFd());
        close(user.getFd());
    }
    else if (user.getIsConnected() && !user.getNickname().empty()) {
       sendResponse(":server_name 462 nick :You may not reregister\r\n" , user.getFd());
       return ;
    }
    else {
       user.setIsConnected(true);
    }
}

Pass::~Pass() {}