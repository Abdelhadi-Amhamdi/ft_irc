/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:33:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 21:54:24 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"

class Kick : public ACommand {
    private:
        std::string comment;
    public:
        Kick();
        void getComment(std::string &buffer);
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Kick();
};
