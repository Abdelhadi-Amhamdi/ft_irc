/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:39:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/29 14:43:55 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <sstream>
#include <sys/socket.h>

class Server;
class Connection;
class Client;

#include "../Client.hpp"
#include "../Replies.hpp"


class ACommand {
    protected:
        std::string res_prefix;
        std::string name;
        std::string Messge;
        std::vector<std::string> params;
        Client *executer;
    public:
        ACommand(const std::string& name);
        int    sendResponse(const std::string &message, int connection_fd);
        virtual ~ACommand();
        virtual void Execute(std::string &buffer, Connection &user, Server &server) = 0;
        void    commandFormater(const std::string& data);
};
