/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:52:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/20 13:37:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"


Pass::Pass() : ACommand("PASS") {}

void Pass::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    if (params[0][0] == ':')
    {
        userInfosChecker(params[0]);
        params.erase(params.begin());
    }
    params.erase(params.begin());
    if (user.getIsConnected())
        sendResponse(":server_name 462 nick :You may not reregister\r\n" , user.getFd());
    else if (server.getPassword() != params[0])
        sendResponse(":server_name 464 nick :Password incorrect\r\n", user.getFd());
    else
        user.setIsConnected(true);
    params.clear();
}

Pass::~Pass() {}