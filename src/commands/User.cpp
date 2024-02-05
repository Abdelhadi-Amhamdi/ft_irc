/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:45:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 17:50:33 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <stdexcept>
#include <string>

User::User() : ACommand("User") {}

void User::Execute(std::string &buffer, Connection &user, Server &server) {
    (void) server;
    commandFormater(buffer);
    
    if (user.getIsAuthentificated())//if is already registred.
        throw std::logic_error(ERR_ALREADYREGISTRED((user.getNickname().empty() ? "" : user.getNickname())));

    if (params.size() < 4)//if dosen't have all parametere.
        throw std::logic_error(ERR_NEEDMOREPARAMS((user.getNickname().empty() ? "" : user.getNickname()), this->name));
    
    std::string& username = params[0];
    user.setUser(username);

    std::string& second = params[1];
    if (second != "0")
        throw std::logic_error("second parametre should be '0'\r\n");
    
    std::string& third = params[2];
    if (third != "*")
        throw std::logic_error("third parametre should be '*'\r\n");
}

User::~User(){}