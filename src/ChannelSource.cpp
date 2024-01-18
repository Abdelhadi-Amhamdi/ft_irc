/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/18 18:16:04 by aamhamdi         ###   ########.fr       */
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

void ChannelSource::addUserToChannel(const std::string &channel_name, const std::string &password, int user_fd, const std::string &user) {
	std::map<std::string, Channel*>::iterator channel = channels.find(channel_name);
	if (channel != channels.end()) {
		if (channel->second->getKey() != password)
			throw std::logic_error("ERR_BADCHANNELKEY");
		if (channel->second->modeExist_invite_only("+i", user_fd))
			throw std::logic_error("ERR_INVITEONLYCHAN");
		if (channel->second->modeExist_users_limit("+l"))
			throw std::logic_error("ERR_CHANNELISFULL");
		channel->second->add_user(user_fd, user, channel_name);
	} else {
		createChannel(channel_name, password);
		// std::string a = ":" + user + " MODE #" + name + " +s \r\n";
		channels[channel_name]->setAdmin(user_fd);
		channels[channel_name]->add_user(user_fd, user, channel_name);
		// send(user_fd, a.c_str(), a.size(), 0);
		// std::cout << a ;
	}
}

void ChannelSource::broadcastMeassges(const std::string &channel_name, const std::string &message, std::string user) {
	std::map<std::string, Channel*>::iterator ch = channels.find(channel_name);
	if (ch != channels.end())
		ch->second->brodcast_msg(message, user);
}


ChannelSource::~ChannelSource(){}