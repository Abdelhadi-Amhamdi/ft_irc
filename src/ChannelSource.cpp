/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/22 09:12:56 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelSource.hpp"

ChannelSource::ChannelSource(){}

void ChannelSource::createChannel(const std::string &channel_name, const std::string &channel_key) {
	Channel* channel = new Channel(channel_name, channel_key);

	this->channels[channel_name] = channel;
}

void ChannelSource::deleteChannel(const std::string &name) {
	std::map<std::string, Channel*>::iterator ch = channels.find(name);
	if (ch != channels.end()) {
		delete ch->second;
		channels.erase(ch);
	}
}

Channel* ChannelSource::getChannelByName(const std::string &channel_name) {
	std::map<std::string, Channel*>::iterator channel = channels.find(channel_name);
	if (channel != channels.end())
		return (channel->second);
	return (NULL);
}

void ChannelSource::addUserToChannel(const int &fd, const std::string &user, const std::string channel_name) {
	std::map<std::string, Channel*>::iterator channel = channels.find(channel_name);
	if (channel != channels.end()) {
		channel->second->setAdmin(fd);
		channel->second->add_user(fd, user);
	}	
}
void ChannelSource::addUserToChannell(const std::string &channel_name, const std::string &password, int user_fd, const std::string &user) {
	std::map<std::string, Channel*>::iterator channel = channels.find(channel_name);
	if (channel != channels.end()) {
		if (channel->second->getKey() != password)
			throw std::logic_error("ERR_BADCHANNELKEY");
		channel->second->add_user(user_fd, user);
	} else {
		createChannel(channel_name, password);
		channels[channel_name]->setAdmin(user_fd);
		channels[channel_name]->add_user(user_fd, user);
	}
}

// void ChannelSource::broadcastMeassges(const std::string &channel_name, const std::string &message, std::string user) {
// 	std::map<std::string, Channel*>::iterator ch = channels.find(channel_name);
// 	if (ch != channels.end())
// 		ch->second->brodcast_msg(message, user);
// }


ChannelSource::~ChannelSource(){}