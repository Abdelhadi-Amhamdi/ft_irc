/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 20:32:35 by kben-ham         ###   ########.fr       */
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

ChannelSource::~ChannelSource(){}
