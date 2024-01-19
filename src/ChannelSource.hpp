/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:18 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 18:24:29 by aamhamdi         ###   ########.fr       */
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
		void setChannelMode(const std::string &channel_name);
		~ChannelSource();
	private:
		std::map<std::string, Channel*> channels;
};
