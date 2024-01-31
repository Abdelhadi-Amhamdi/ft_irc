/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:11:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/30 16:11:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include "ACommand.hpp"
#include "../Server.hpp"
#include <curl/curl.h>
#include <map>

class Bot : public ACommand {
    private:
        std::string data;
        const std::string prefix;
        std::map<std::string,std::pair<std::string, std::string> > manual;
    public:
        Bot();
        void Manual(const int &fd);
        void Weather(const int &fd);
        void ServerInfos(Server &server, const int &fd);
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Bot();
};
