/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:01 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/24 17:01:54 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"

class Client;

class Nick : public ACommand {

    public:
        Nick();
        bool isValidNickname(const std::string &nickname) const;
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Nick();
};
