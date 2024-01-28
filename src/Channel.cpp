/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/27 04:02:44 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "color.hpp"

Channel::Channel(const std::string &channel_name, const std::string &channel_key) 
    :  name(channel_name), mode(channel_key){}

void Channel::addAdmin(const int &user_fd) {
    admins.push_back(user_fd);
}

void Channel::addInvite(const int &user_fd) {
    std::vector<int>::iterator it = std::find(invites.begin(), invites.end(), user_fd);
    if (it == invites.end())
        invites.push_back(user_fd);
}

void Channel::delInvite(const int &fd) {
  std::vector<int>::iterator it = std::find(invites.begin(), invites.end(), fd);
  if (it != invites.end())
    invites.erase(it);
}

const std::string &Channel::getName() const {
    return (name);
}

void Channel::setTopic(const std::string &topic) {
    this->topic = topic;
}

const std::string &Channel::getTopic() const {
    return (topic);
}

void Channel::delAdmin(const int &user_fd) {
    std::vector<int>::iterator it = std::find(admins.begin(), admins.end(), user_fd);
    if (it != admins.end())
        admins.erase(it);
}

ChannelMode& Channel::getMode() {
    return mode;
}

size_t Channel::getMembersCount() const {
    return (members.size());
}

std::string Channel::generateMemebrsList() {
    std::string members_list = ":server_name 353 nick = #" + name + "   :";
    for (std::map<int, std::string>::iterator it = members.begin(); it != members.end(); it++) {
        if (std::find(admins.begin(), admins.end(), it->first) != admins.end())
            members_list += "@";
        members_list += it->second;
        members_list += " ";
    }
    members_list += "\r\n";
    return (members_list);
}

void Channel::addUserToChannel(const int &fd, const std::string &user) {
    members[fd] = user;
}

bool Channel::isMemberInChannel(const int &fd) {
    std::map<int, std::string>::iterator it = members.find(fd);
    if (it != members.end())
        return (true);
    return (false);
}

void Channel::delUserFromChannel(const int &fd) {
    std::map<int, std::string>::iterator it = members.find(fd);
    if (it != members.end()) {
        delAdmin(fd);
        members.erase(it);
    }
}

void Channel::broadCastResponse(const std::string &message) {
    std::map<int, std::string>::iterator it = members.begin();
    for (; it != members.end(); it++) {
        send(it->first, message.c_str(), message.size(), 0);
    }   
}


void Channel::brodCastMessage(const std::string &message, const std::string &user_name) {
    std::map<int, std::string>::iterator it = members.begin(); 
    for (; it != members.end(); it++) {
        if (it->second == user_name)
            continue;
        std::string response = ":" + user_name + " PRIVMSG #" + name + " :" + message + "\r\n";
        send(it->first, response.c_str(), response.size(), 0);
    }
}

bool Channel::checkIfAdmin(const int &user_fd) {
    std::vector<int>::iterator it = std::find(admins.begin(), admins.end(), user_fd);
    if (it != admins.end())
        return (true);
    return (false);
}

bool Channel::checkIfInvited(const int &user_fd) {
    std::vector<int>::iterator it = std::find(invites.begin(), invites.end(), user_fd);
    if (it != invites.end())
        return (true);
    return (false);
}

Channel::~Channel(){
    std::cout << "Channel destroyed" << std::endl;
}
