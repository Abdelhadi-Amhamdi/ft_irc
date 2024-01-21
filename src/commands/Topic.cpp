/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:53:32 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/21 19:27:25 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"



#define ERR_NOSUCHCHANNEL ":server_name 403 Topic <channel> :No such channel\r\n"
#define ERR_NOTONCHANNEL ": server_name 442 Topic <channel> :You're not on that channel\r\n"
#define ERR_NEEDMOREPARAMS  ": server_name 461 <client> <command> :Not enough parameters\r\n"
#define ERR_CHANOPRIVSNEEDED  ": server_name 482 <client> <command> :You're not channel operator\r\n"

Topic::Topic() : ACommand("Topic") {}

void Topic::Execute(std::string &buffer, Connection &user, Server &server)
{
    commandFormater(buffer);
    // ClientSource *client_manager = server.getClientManager();
    ChannelSource *channel_manager = server.getChannelManager();
    if (params[0][0] == ':')
    {
        userInfosChecker(params[0]);//not_yet
    	// throw std::logic_error("ERR_NOTONCHANNEL");
        params.erase(params.begin());
    }
    params.erase(params.begin());
    if (params[0][0] == '#')
        params[0].erase(params[0].begin());
    Channel *tmp = channel_manager->getChannelByName(params[0]);
    if (tmp == NULL)
    	throw std::logic_error("ERR_NOSUCHCHANNEL");
    else
    {
        if (!params[1].empty())
    	    std::cout << tmp->getTopic();

        if (params[1][0] == ':')
        {
            params[1].erase(params[1].begin());
            //set_topic after check mode
    	    // throw std::logic_error("ERR_CHANOPRIVSNEEDED");
            tmp->setTopic(params[1]);
        }
        else
    	    throw std::logic_error("ERR_NEEDMOREPARAMS");
        
    }
    std::string message = "sets topic:" + params[1];
    //check broadcast
    channel_manager->broadcastMeassges(params[0], message, user.getNickname());
    params.clear();
}

Topic::~Topic(){}