/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:54:14 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/21 21:42:07 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Quit.hpp"

Quit::Quit() : ACommand("Quit") {}

void Quit::Execute(std::string &buffer, Connection &user, Server &server)
{
    commandFormater(buffer);
    userInfosChecker();
    // ClientSource *client_manager = server.getClientManager();
    ChannelSource *channel_manager = server.getChannelManager();
    std::string message = "Quit: ";
    if (!params[0].empty())
    {
        //broadcast to all channels 
        channel_manager->broadcastMeassges(params[0], message, user.getNickname());
        // close fd_client;
        close (user.fd);
    }
    else
    {
        if (params[0][0] == ':')
        {
            params[0].erase(params[0].begin());
            std::string message += params[0] ;
            channel_manager->broadcastMeassges(params[0], message, user.getNickname());
        }
        else
            throw std::logic_error("ERR");
        
    }
    params.clear();
}

Quit::~Quit(){}