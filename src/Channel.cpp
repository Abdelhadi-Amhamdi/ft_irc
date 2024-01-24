/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 22:33:35 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sys/socket.h>
#include "color.hpp"

Channel::Channel(const std::string &channel_name, const std::string &channel_key) 
    : name(channel_name), key(channel_key) {}

void Channel::addAdmin(const int &user_fd) {
    admins.push_back(user_fd);
}

const std::string &Channel::getName() const {
    return (name);
}

void Channel::delAdmin(const int &user_fd) {
    std::vector<int>::iterator it = std::find(admins.begin(), admins.end(), user_fd);
    if (it != admins.end())
        admins.erase(it);
}

void Channel::setMode(const std::string &mode) {
    modes.push_back(mode);
}

const std::string & Channel::getKey() const {
    return (this->key);
}

size_t Channel::getMembersCount() const {
    return (members.size());
}

std::string Channel::generateMemebrsList() {
    std::string members_list = ":server_name 353 nick = #" + name + "   :";
    for (std::vector<std::pair<int, std::string> >::iterator it = members.begin(); it != members.end(); it++) {
        if (std::find(admins.begin(), admins.end(), it->first) != admins.end())
            members_list += "@";
        members_list += it->second;
        members_list += " ";
    }
    members_list += "\r\n";
    return (members_list);
}

void Channel::addUserToChannel(const int &fd, const std::string &user) {
    members.push_back(std::make_pair(fd, user));
}

void Channel::delUserFromChannel(const int &fd) {
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].first == fd) 
        {
            delAdmin(fd);
            std::vector<std::pair<int, std::string> >::iterator item = members.begin() + i;
            members.erase(item);
        }
    }
}

void Channel::broadCastResponse(const std::string &message) {
    std::vector<std::pair<int, std::string> >::iterator it = members.begin();
    for (; it != members.end(); it++) {
        send(it->first, message.c_str(), message.size(), 0);
    }   
}

void Channel::brodCastMessage(const std::string &message, const std::string &user_name) {
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].second == user_name)
            continue;
        std::string response = ":" + user_name + " PRIVMSG #" + name + " :" + message + "\r\n";
        send(members[i].first, response.c_str(), response.size(), 0);
    }
}

bool Channel::checkIfAdmin(const int &user_fd) {
    std::vector<int>::iterator it = std::find(admins.begin(), admins.end(), user_fd);
    if (it != admins.end())
        return (true);
    return (false);
}

Channel::~Channel(){
    std::cout << "Channel destroyed" << std::endl;
}
