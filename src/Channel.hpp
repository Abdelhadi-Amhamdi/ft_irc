/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 19:51:08 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <sys/socket.h>

class Channel {
    private:
        // size_t users_limit;
        std::string topic;
        std::string name;
        std::string key;
        std::vector<int> admins;
        std::vector<std::string> modes;
        std::vector<int> invites;
        std::vector<std::pair<int, std::string> > members;
    public:
        // Channel(const std::string &channel_name, const std::string &channel_key);
        // Channel(int admin, std::string topic, std::string name);
        // void add_user(int fd, const std::string &user, const std::string &channel);
        void ClientResponse(int client_fd, const std::string &username, const std::string &channel_name);
        // void brodcast_msg(std::string msg, std::string &user);
        // void brodcast_msg(std::string msg, std::string &user_name, const std::string &channel);
        void setTopic(std::string new_topic);
        const std::string & getTopic() const;
        void setAdmin(const int &user_fd);
        void setMode(const std::string &mode);
        const std::string & getKey() const ;
        const std::vector<std::pair<int, std::string> > & getMembers() const ;
        
        Channel(const std::string &channel_name, const std::string &channel_key);
        std::string generateMemebrsList(const std::string &username);
        void add_user(const int &fd, const std::string &user);
        void ClientResponse(const int &client_fd, const std::string &username);
        void brodCastMessage(const std::string &message, const std::string &user);
        void to_all(const std::string &message, const std::string &user);
        // int modeExist_users_limit(const std::string &mode);
        // int modeExist_invite_only(const std::string &mode, int user_fd);
        ~Channel();
};


