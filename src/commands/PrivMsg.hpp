/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:43:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/22 09:53:19 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"

class PrivMsg: public ACommand {
    private:
        std::string channel_name;
        std::string message;
    public:
        PrivMsg();
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~PrivMsg();
};
