/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:52:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/31 18:52:58 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include <stdexcept>
#include <string>

Pass::Pass() : ACommand("PASS") {}

void Pass::Execute(std::string &buffer, Connection &user, Server &server) {
    commandFormater(buffer);
    if (!params.size())
        throw std::logic_error(ERR_NEEDMOREPARAMS(std::string(""), this->name));
    if (user.getIsAuthentificated() == true || !user.getNickname().empty())
        throw std::logic_error(ERR_ALREADYREGISTRED(user.getNickname()));
    
    std::string& pass = params[0];
    if (server.getPassword() != pass)
    {
        user.setPass("");
        throw std::logic_error(ERR_BADPASS);
    }
    user.setPass(pass);
}

Pass::~Pass() {}