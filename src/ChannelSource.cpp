/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/05 13:51:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelSource.hpp"

ChannelSource::ChannelSource(){}

void ChannelSource::createChannel(const std::string &channel_name) {
	Channel* channel = new Channel(channel_name);

	this->channels[channel_name] = channel;
}

void ChannelSource::deleteChannel(const std::string &name) {
	std::map<std::string, Channel*>::iterator ch = channels.find(name);
	if (ch != channels.end()) {
		delete ch->second;
		channels.erase(ch);
	}
}

size_t ChannelSource::getChannelsCount() const {
	return (channels.size());
}

Channel* ChannelSource::getChannelByName(const std::string &channel_name) {
	std::map<std::string, Channel*>::iterator channel = channels.find(channel_name);
	if (channel != channels.end())
		return (channel->second);
	return (NULL);
}

ChannelSource::~ChannelSource(){
	std::map<std::string, Channel*>::iterator it = channels.begin();
	for (; it != channels.end(); it++)
		delete it->second;
	channels.clear();
}
