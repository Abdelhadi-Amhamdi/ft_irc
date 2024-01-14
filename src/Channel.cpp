/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 14:17:59 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sys/socket.h>
#include "color.hpp"

void Channel::setadmin(int fd) {
    this->admin_fd = fd;
}

// Channel::Channel(int fd, std::string topic, std::string name)
//     : topic(topic), channel_name(name) {
//         if (members.empty())
//             admin_fd = fd;
//         std::cout << "Channel created" << std::endl;
//         add_user(fd);
// }

void Channel::add_user(int fd, const std::string &user, const std::string &channel) {
    members.push_back(std::make_pair(fd, user));
    std::string msg = "fd: " + std::to_string(fd) + " added to channel\n";
    
    std::string join_message = ":" + user + " JOIN #" + channel + "\r\n";
    send(fd, join_message.c_str(), join_message.size(), 0);

    std::string usersList_message = ":localhost 353 " + user + " = #" + channel + " :";
    for (std::vector<std::pair<int, std::string> >::iterator it = members.begin(); it != members.end(); it++) {
       usersList_message += it->second;
       usersList_message += " ";
    }
    usersList_message += "\r\n";
    send(fd, usersList_message.c_str(), usersList_message.size(), 0);

    std::string RPL_ENDOFNAMES = user + ":localhost 366 " + user + " #" + channel + " :End of /NAMES list.\r\n";
    send(fd, RPL_ENDOFNAMES.c_str(), RPL_ENDOFNAMES.size(), 0);
    
    brodcast_msg(msg, fd, user, channel);
}


void Channel::brodcast_msg(std::string msg) {

    
    (void)msg;

}


Channel::~Channel(){
    std::cout << "Channel destroyed" << std::endl;
}