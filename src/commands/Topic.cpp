/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:53:32 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/24 17:02:03 by kben-ham         ###   ########.fr       */
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
    std::string message;
    commandFormater(buffer);
    userInfosChecker();
    ChannelSource *channel_manager = server.getChannelManager();
    if (params[0][0] == '#')
        params[0].erase(params[0].begin());
    Channel *tmp = channel_manager->getChannelByName(params[0]);
    if (tmp == NULL)
    {
        message = ":" +  user.getNickname()+" 442 " + user.getNickname() + " #" + params[0] + " :You're not on that channel " + "\r\n";
        sendResponse(message, user.getFd());
    }
    else
    {
        int a  = params.size();
        if (a == 1)
        {
            std::string topic = tmp->getTopic();
            if (topic.empty())
                message = ":" + user.getNickname() + " 331 "+ user.getNickname() + " #" + params[0] + " :No topic is set.\r\n";
            else  
                message = ":" +  user.getNickname()+ " 332 " + user.getNickname() + " #" + params[0] + " " + topic + "\r\n";
            sendResponse(message, user.getFd());
        }
        else if (params[1][0] == ':')
        {
            params[1].erase(params[1].begin());
            //set_topic after check mode (if +t "just operators can change it else throw above")
            // :irc.example.com 482 dan #v5 :You're not channel operator
    	    // ERR_CHANOPRIVSNEEDED
            tmp->setTopic(params[1]);
            message = ":" +  user.getNickname() + " TOPIC #" + params[0] + " " + params[1] + " \r\n";
            tmp->broadCastResponse(message);
        }
        else
            sendResponse(": server_name 461 <client> <command> :Not enough parameters\r\n", user.getFd());
        params.clear();
    }
}

Topic::~Topic(){}