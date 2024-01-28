/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:22:21 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/28 19:07:19 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "ACommand.hpp"
#include "../Server.hpp"



class Join : public ACommand {
    private:
        std::vector<std::pair<std::string, std::string> > channels;
    public:
        Join();
        void channels_formater();
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Join();
};
