/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:54:14 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/31 09:42:05 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Quit.hpp"

Quit::Quit() : ACommand("Quit") {}

void Quit::Execute(std::string &buffer, Connection &user, Server &server)
{
	ClientSource &client_manager = server.getClientManager();
	Client *tmp_client = client_manager.getClientByNickname(user.getNickname());
	std::vector<std::string> joined_channels = tmp_client->getgroupsin();
	int len = joined_channels.size();
	std::string message_to_send;
	std::string message = " QUIT :";
	commandFormater(buffer);
	if (params.size() != 0)
	{
		if (params[0][0] == ':')
		{
			params[0].erase(params[0].begin());
			message += params[0];
		}
		for (size_t i = 1; i < params.size(); i++)
			message +=  " " + params[i];
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
	server.deleteConnection(user.getFd());
	server.deleteConnectionFd(user.getFd());
	close(user.getFd());
	client_manager.deleteClient(user.getNickname());
	params.clear();
}

Quit::~Quit(){}
