/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:54:14 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/24 17:42:02 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Quit.hpp"

Quit::Quit() : ACommand("Quit") {}

void Quit::Execute(std::string &buffer, Connection &user, Server &server)
{
	ClientSource *client_manager = server.getClientManager();
	Client *tmp_client = client_manager->getClientByNickname(user.getNickname());
	std::vector<std::string> k = tmp_client->getgroupsin();
	int a = k.size();
	std::string c;
	std::string message = " QUIT :";
	commandFormater(buffer);
	userInfosChecker();
	if (params.size() != 0)
	{
		if (params[0][0] == ':')
		{
			params[0].erase(params[0].begin());
			message += params[0];
		}
	}
	ChannelSource *channel_manager = server.getChannelManager();
	Channel *tmp;
	c = ":" + user.getNickname() + message + "\r\n";
	for (int i = 0; i < a; i++)
	{
	   tmp = channel_manager->getChannelByName(k[i]);
	   tmp->broadCastResponse(c);
	   tmp->delUserFromChannel(user.getFd());
	}
	close(user.getFd());
	client_manager->deleteClient(user.getNickname());
	params.clear();
}

Quit::~Quit(){}
