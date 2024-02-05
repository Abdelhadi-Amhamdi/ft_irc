/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:44:55 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/25 23:27:27 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"

class User : public ACommand {
    private:
        std::string user_name; 
    public:
        User();
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~User();
};