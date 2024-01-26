/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:05:18 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/26 01:31:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <map>
#include "Channel.hpp"

class ChannelSource {
	public:
		ChannelSource();
		void		createChannel(const std::string &channel_name, const std::string &channel_key);
		void		deleteChannel(const std::string &name);
		Channel*	getChannelByName(const std::string &name);
		size_t		getChannelsCount() const;
		~ChannelSource();
	private:
		std::map<std::string, Channel*> channels;
};
