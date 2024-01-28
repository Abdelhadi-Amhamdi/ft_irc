/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:52:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/28 15:53:54 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

Pass::Pass() : ACommand("PASS") {}

void Pass::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    if (params.size() && server.getPassword() != params[0]) {
        sendResponse(ERR_BADPASS, user.getFd());
        close(user.getFd());
    }
    else if (user.getIsConnected() && !user.getNickname().empty()) {
       throw sendResponse(ERR_ALREADYREGISTRED(user.getNickname()) , user.getFd());
       return ;
    }
    else {
       user.setIsConnected(true);
    }
}

Pass::~Pass() {}