/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 19:35:49 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include <stdexcept>

Nick::Nick() : ACommand("Nick") {}

bool Nick::isValidNickname(const std::string &nickname) const {
    if (nickname.size() > 9)
        return (false);
    if (nickname.find("#") != std::string::npos)
        return (false);
    if (std::isdigit(nickname[0]) || nickname[0] == ':')
        return (false);
    return (true);
}

void Nick::Execute(std::string &buffer, Connection &user, Server &server) {
    ClientSource &client_manager = server.getClientManager();
    commandFormater(buffer);

    if (params.empty())
        throw std::logic_error(ERR_NONICKNAME(user.getNickname()));
    
    std::string&    nick = params[0];
    std::string     userNickname = user.getNickname();
    if (params.size() > 1 || isValidNickname(nick) == false)
        throw std::logic_error(ERR_ERRONNICK((userNickname.empty() ? "" : userNickname), nick));
    
    user.setNickname(nick, client_manager);
    sendResponse("your are now known as " + nick + "\r\n", user.getFd());
}

Nick::~Nick(){}