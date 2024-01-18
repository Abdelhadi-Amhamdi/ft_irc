/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:55:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/18 18:08:31 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ACommand.hpp"
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"
#include <sstream>
#include <string>

#define ERR_NEEDMOREPARAMS ":server_name 461 nick JOIN :Not enough parameters\r\n"
#define ERR_INVITEONLYCHAN ":server_name 437 nick <channel> :Cannot join channel (+i)\r\n"
#define ERR_CHANNELISFULL ":server_name 471 nick <channel> :Cannot join channel (+l)\r\n"
#define ERR_BADCHANNELKEY ":server_name 475 nick <channel> :Cannot join channel (+k)\r\n"

class Join : public ACommand {
    public:
        Join();
        void join_response(int client_fd, const std::string &username, const std::string &response) const;
        void channels_formater(std::string &data, std::vector<std::pair<std::string, std::string> > &channels) const;
        void exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &serve) const;
        ~Join();
    private:
};
