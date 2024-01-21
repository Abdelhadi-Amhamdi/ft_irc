/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 21:59:36 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sys/socket.h>
#include "color.hpp"

Channel::Channel(const std::string &channel_name, const std::string &channel_key) 
    : users_limit(2), name(channel_name), key(channel_key) {
        // modes.push_back("+l");
    }

void Channel::setAdmin(int user_fd) {
    admins.push_back(user_fd);
}

void Channel::setTopic(std::string new_topic) {
   this->topic = new_topic;
}

void Channel::setMode(std::string &mode) {
    modes.push_back(mode);
}
const std::string & Channel::getTopic()const {
    return (this->topic);
}
const std::string & Channel::getKey() const {
    return (this->key);
}


int Channel::modeExist_invite_only(const std::string &mode, int user_fd) {
    std::vector<std::string>::iterator m = std::find(modes.begin(), modes.end(), mode);
    if (m != modes.end()) {
        if (std::find(invites.begin(), invites.end(), user_fd) == invites.end())
            return (1);
    }
    return (0);
}
int Channel::modeExist_users_limit(const std::string &mode) {
    std::vector<std::string>::iterator m = std::find(modes.begin(), modes.end(), mode);
    if (m != modes.end() && members.size() == users_limit)
        return (1);
    return (0);
}

void Channel::ClientResponse(int client_fd, const std::string &username, const std::string &channel_name) { 
    (void)channel_name;
    (void)username;  
    std::string c = ":" + username + " JOIN #" + channel_name + "\r\n";
    send(client_fd, c.c_str(), c.size(), 0);
    std::string b = ":localhost 353 " + username + " = #" + channel_name + " :" + username + "\r\n";
    // for (std::vector<std::pair<int, std::string> >::iterator it = members.begin(); it != members.end(); it++) {
    //     // if (std::find(admins.begin(), admins.end(), it->first) != admins.end())
    //     //     usersList_message += "@";
    //     usersList_message += it->second;
    //     usersList_message += " ";
    // }
    // usersList_message.erase(usersList_message.end()-1);
    // usersList_message += "\r\n";
    // std::cout << usersList_message;
    send(client_fd, b.c_str(), b.size(), 0);

    std::string a = ":localhost 366 " + username + " #" + channel_name + " :End of /NAMES list.\r\n";
    send(client_fd, a.c_str(), a.size(), 0);
}

void Channel::add_user(int fd, const std::string &user, const std::string &channel) {
    members.push_back(std::make_pair(fd, user));
    

    for (std::vector<std::pair<int, std::string> >::iterator it = members.begin(); it != members.end(); it++)
        ClientResponse(it->first, it->second, channel);
}

void Channel::brodcast_msg(std::string msg, std::string &user_name) {
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].second == user_name)
            continue;
        std::string a = ":" + user_name + " PRIVMSG #irc :" + msg + "\r\n";
        send(members[i].first, a.c_str(), a.size(), 0);
    }
}


Channel::~Channel(){
    std::cout << "Channel destroyed" << std::endl;
}