/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:54:14 by kben-ham          #+#    #+#             */
/*   Updated: 2024/02/04 13:09:30 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"

Quit::Quit() : ACommand("Quit") {}

void Quit::Execute(std::string &buffer, Connection &user, Server &server)
{
	ClientSource &client_manager = server.getClientManager();
	Client *tmp_client = client_manager.getClientByNickname(user.getNickname());
	if (!tmp_client)
		return ;
	std::vector<std::string> joined_channels = tmp_client->getgroupsin();
	int len = joined_channels.size();
	std::string message_to_send;
	std::string message = " QUIT :";
	commandFormater(buffer);
	if (params.size() != 0)
	{
		params[0] = get_message(buffer, params[0]);
		if (params[0][0] == ':')
		{
			params[0].erase(params[0].begin());
			message += params[0];
		}
	}
	ChannelSource &channel_manager = server.getChannelManager();
	Channel *tmp;
	message_to_send = ":" + user.getNickname() + message + "\r\n";
	for (int i = 0; i < len; i++)
	{
	   tmp = channel_manager.getChannelByName(joined_channels[i]);
	   tmp->broadCastResponse(message_to_send);
	   tmp->delUserFromChannel(user.getFd());
	}
	client_manager.deleteClient(user.getNickname());
}

Quit::~Quit(){}
