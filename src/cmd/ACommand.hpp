/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:24:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 13:39:40 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "../Client.hpp"
class Server;

class ACommand {
    public:
        ACommand(const std::string &name);
        virtual void exec(const std::string &pass, Client &client, const Server &server) const = 0;
        virtual ~ACommand();
    private:
        const std::string name;
};
