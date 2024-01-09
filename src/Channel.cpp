/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/09 01:06:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sys/socket.h>
#include "color.hpp"

Channel::Channel(int fd, std::string topic, std::string name)
    : topic(topic), channel_name(name) {
        if (members.empty())
            admin_fd = fd;
        std::cout << "Channel created" << std::endl;
        add_user(fd, name);
}

void Channel::add_user(int fd, std::string nickname) {
    members.push_back(fd);
    std::string msg = "fd: " + std::to_string(fd) + " added to channel " + nickname + "\n";
    brodcast_msg(msg);
}


void Channel::brodcast_msg(std::string msg) {
    for (std::vector<int>::iterator it = members.begin(); it != members.end(); it++) {
        std::cout << "member => " << *it << std::endl;
        send(*it, msg.c_str(), msg.size(), 0);
    }    
}


Channel::~Channel(){
    std::cout << "Channel destroyed" << std::endl;
}