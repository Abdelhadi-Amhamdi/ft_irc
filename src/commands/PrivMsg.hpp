/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:43:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 15:14:00 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"

class PrivMsg: public ACommand {
    private:
        std::string message;
        std::string targets;
        std::string target;
    public:
        PrivMsg();
        void commandArgsChecker(std::string &buffer, const int &fd);
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~PrivMsg();
};
