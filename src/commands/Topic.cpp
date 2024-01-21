/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:53:32 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/21 16:18:39 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"



#define ERR_NOSUCHCHANNEL ":server_name 403 Topic <channel> :No such channel\r\n"
#define ERR_NOTONCHANNEL ": server_name 442 Topic <channel> :You're not on that channel\r\n"
Topic::Topic() : ACommand("Topic") {}

void Topic::Execute(std::string &buffer, Connection &user, Server &server)
{
    // (void)user;
    commandFormater(buffer);
    if (params[0][0] == ':')
    {
        userInfosChecker(params[0]);
        params.erase(params.begin());
    }
    // ClientSource *client_manager = server.getClientManager();
    ChannelSource *channel_manager = server.getChannelManager();
    
    if (params[0][0] == '#')
        params.erase(params.begin());
    Channel *tmp = channel_manager->getChannelByName(params[0]);
    //if it returns null you should print an error
    if (tmp == NULL)
			throw std::logic_error("ERR_NOSUCHCHANNEL");
    if (tmp != NULL)
    {
        if (params[1][0] == ':')
            params.erase(params.begin());
        //set_topic after check mode
        tmp->setTopic(params[1]);
    }
    std::string message = "sets topic:" + params[1];
    channel_manager->broadcastMeassges(params[0], message, user.getNickname());
    params.clear();
}

Topic::~Topic(){}