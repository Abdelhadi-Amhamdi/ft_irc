/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:27:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/26 16:08:06 by aamhamdi         ###   ########.fr       */
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
        void getReason();
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Part();
};
