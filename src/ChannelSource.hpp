/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:18 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 13:27:38 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <map>
#include "Channel.hpp"

class ChannelSource {
	public:
		ChannelSource();
		void createChannel(const std::string &channel_name, const std::string &channel_key);
		void deleteChannel(const std::string &name);
		void addUserToChannel(const std::string &channel, const std::string &password, int user_fd, const std::string &user);
		void broadcastMeassges(const std::string &channel_name, const std::string &message, std::string user);
		Channel* getChannelByName(const std::string &name);
		~ChannelSource();
	private:
		std::map<std::string, Channel*> channels;
};
