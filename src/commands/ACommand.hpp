/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:39:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/20 13:27:17 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <sstream>
#include <sys/socket.h>

class Server;
class Connection;


class ACommand {
    protected:
        std::string name;
        std::string Messge;
        std::vector<std::string> params;
    public:
        ACommand(const std::string& name);
        void    sendResponse(const std::string &message, int connection_fd);
        virtual ~ACommand();
        virtual void Execute(std::string &buffer, Connection &user, Server &server) = 0;
        void    userInfosChecker(const std::string &user_info);
        void    commandFormater(const std::string& data);
};
