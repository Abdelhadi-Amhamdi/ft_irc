/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:43:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/25 17:50:24 by aamhamdi         ###   ########.fr       */
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
        bool commandArgsChecker(const int &fd);
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~PrivMsg();
};
