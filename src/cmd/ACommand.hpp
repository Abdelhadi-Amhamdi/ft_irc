/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:24:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/15 19:02:01 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "../Client.hpp"
#include <sstream>

class Server;

class ACommand {
    public:
        ACommand();
        virtual void exec(std::string &user_infos,std::string &cmd_params, Client &client, Server &server) const = 0;
        virtual ~ACommand();
    private:
};
