/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:45:01 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 23:01:23 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"

class Invite : public ACommand {
    public:
        Invite();
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Invite();
};
