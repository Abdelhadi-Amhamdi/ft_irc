/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:05 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/11 16:22:11 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include <map>
#include <stdexcept>
#include <string>

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
    
    // sendResponse(RPL_NICK(user.getNickname(), user.getUser(), user.getHostname(), nick), user.getFd());
    user.setNickname(nick, client_manager);
    client_manager.print();
}

Nick::~Nick(){}