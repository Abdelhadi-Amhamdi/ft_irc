/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:33:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 15:29:11 by kben-ham         ###   ########.fr       */
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
