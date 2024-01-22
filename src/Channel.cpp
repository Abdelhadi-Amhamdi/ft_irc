/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/22 10:28:47 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sys/socket.h>
#include "color.hpp"

Channel::Channel(const std::string &channel_name, const std::string &channel_key) 
    : name(channel_name), key(channel_key) {}

void Channel::setAdmin(const int &user_fd) {
    admins.push_back(user_fd);
}

void Channel::setMode(const std::string &mode) {
    modes.push_back(mode);
}

const std::string & Channel::getKey() const {
    return (this->key);
}

std::string Channel::generateMemebrsList(const std::string &username) {
    std::string members_list = ":server_name 353 " + username + " = #" + name + "   :";
    for (std::vector<std::pair<int, std::string> >::iterator it = members.begin(); it != members.end(); it++) {
        if (std::find(admins.begin(), admins.end(), it->first) != admins.end())
            members_list += "@";
        members_list += it->second;
        members_list += " ";
    }
    members_list += "\r\n";
    return (members_list);
}

void Channel::ClientResponse(const int &client_fd, const std::string &username) { 
    std::string join_message = ":" + username + " JOIN #" + name + "\r\n";
    send(client_fd, join_message.c_str(), join_message.size(), 0);
    
    std::string members_list = generateMemebrsList(username);
    send(client_fd, members_list.c_str(), members_list.size(), 0);

    std::string end_list_message = ":server_name 366 " + username + " " + name + " :End of /NAMES list.\r\n";
    send(client_fd, end_list_message.c_str(), end_list_message.size(), 0);
}

void Channel::add_user(const int &fd, const std::string &user) {
    members.push_back(std::make_pair(fd, user));
    std::vector<std::pair<int, std::string> >::iterator it = members.begin();
    for (; it != members.end(); it++)
        ClientResponse(it->first, it->second);
}

void Channel::brodCastMessage(const std::string &message, const std::string &user_name) {
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].second == user_name)
            continue;
        std::string message = ":" + user_name + " PRIVMSG #" + name + " :" + message + "\r\n";
        send(members[i].first, message.c_str(), message.size(), 0);
    }
}

Channel::~Channel(){
    std::cout << "Channel destroyed" << std::endl;
}

// int Channel::modeExist_invite_only(const std::string &mode, int user_fd) {
//     std::vector<std::string>::iterator m = std::find(modes.begin(), modes.end(), mode);
//     if (m != modes.end()) {
//         if (std::find(invites.begin(), invites.end(), user_fd) == invites.end())
//             return (1);
//     }
//     return (0);
// }

// int Channel::modeExist_users_limit(const std::string &mode) {
//     std::vector<std::string>::iterator m = std::find(modes.begin(), modes.end(), mode);
//     if (m != modes.end() && members.size() == users_limit)
//         return (1);
//     return (0);
// }