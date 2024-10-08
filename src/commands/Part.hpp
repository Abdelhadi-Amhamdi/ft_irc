/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:27:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 15:44:34 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"



class Part : public ACommand {
    private:
        std::string reason;
    public:
        Part();
        void getReason(std::string &buffer);
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Part();
};
