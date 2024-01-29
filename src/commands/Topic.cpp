/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:53:32 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/29 17:53:29 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

// #define ERR_NOSUCHCHANNEL ":server_name 403 Topic <channel> :No such channel\r\n"
// #define ERR_NOTONCHANNEL ": server_name 442 Topic <channel> :You're not on that channel\r\n"
// #define ERR_NEEDMOREPARAMS  ": server_name 461 <client> <command> :Not enough parameters\r\n"
// #define ERR_CHANOPRIVSNEEDED  ": server_name 482 <client> <command> :You're not channel operator\r\n"
// #define ERR_NOSUCHCHANNEL ":server_name 403 Topic <channel> :No such channel\r\n"
// #define ERR_NOTONCHANNEL ": server_name 442 Topic <channel> :You're not on that channel\r\n"
// #define ERR_NEEDMOREPARAMS  ": server_name 461 <client> <command> :Not enough parameters\r\n"
// #define ERR_CHANOPRIVSNEEDED  ": server_name 482 <client> <command> :You're not channel operator\r\n"

Topic::Topic() : ACommand("Topic") {}

void Topic::Execute(std::string &buffer, Connection &user, Server &server)
{
	std::string message, topic;
	commandFormater(buffer);
	ChannelSource *channel_manager = server.getChannelManager();
	ClientSource *client_manager = server.getClientManager();
	Client *tmp_client = client_manager->getClientByNickname(user.getNickname());
	int a  = params.size();
	if (params[0] == ":")
	{
		sendResponse(":server_name 461 topic :TOPIC Not enough parameters\r\n", user.getFd());
		return;
	}
	if (params[0][0] == '#')
		params[0].erase(params[0].begin());
	Channel *tmp = channel_manager->getChannelByName(params[0]);
	if (tmp == NULL)
		sendResponse(":server_name 403 Topic #" +params[0] + " :No such channel\r\n", user.getFd());
	else
	{
		std::vector<std::string> k = tmp_client->getgroupsin();
		std::vector<std::string>::iterator it = std::find(k.begin(), k.end(), params[0]);
    	if (it == k.end())
		{
			sendResponse(":" +  user.getNickname()+" 442 " + user.getNickname() + " #" + params[0] + " :You're not on that channel " + "\r\n", user.getFd());
			return;
		}
		a  = params.size();
		if (a == 1)
		{
			topic = tmp->getTopic();
			if (topic.empty())
				message = ":" + user.getNickname() + " 331 "+ user.getNickname() + " #" + params[0] + " :No topic is set.\r\n";
			else  
				message = ":" +  user.getNickname()+ " 332 " + user.getNickname() + " #" + params[0] + " :" + topic + "\r\n";
			sendResponse(message, user.getFd());
		}
		else 
		{
			if (params[1][0] == ':')
				params[1].erase(params[1].begin());
			if (a > 1)
			{
				for (size_t i = 2; i < params.size(); i++)
					params[1] +=  " " + params[i];
			}
			ChannelMode channel_mode = tmp->getMode();
			if (channel_mode.getTopic() == true)
			{
				if (tmp->checkIfAdmin(user.getFd()) == false)
				{
					sendResponse(":" + user.getNickname() + " 482 "+ user.getNickname() + " #" + params[0] + " :You're not channel operator\r\n", user.getFd());
					return;
				}
			}
			tmp->setTopic(params[1]);
			message = ":" +  user.getNickname() + " TOPIC #" + params[0] + " :" + params[1] + " \r\n";
			tmp->broadCastResponse(message);
		}
   }
}

Topic::~Topic(){}