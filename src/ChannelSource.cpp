/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:35:25 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelSource.hpp"

ChannelSource::ChannelSource(){}

void ChannelSource::createChannel(const std::string &name) {
	Channel* channel = new Channel();

	this->channels[name] = channel;
}

void ChannelSource::deleteChannel(const std::string &name) {
	std::map<std::string, Channel*>::iterator ch = channels.find(name);
	if (ch != channels.end()) {
		delete ch->second;
		channels.erase(ch);
	}
}

void ChannelSource::addUserToChannel(const std::string &name, int user_fd, const std::string &user) {
	std::map<std::string, Channel*>::iterator ch = channels.find(name);
	if (ch != channels.end()) {
		ch->second->add_user(user_fd, user, name);
	} else {
		createChannel(name);
		channels[name]->add_user(user_fd, user, name);
		channels[name]->setadmin(user_fd);
	}
}


ChannelSource::~ChannelSource(){}