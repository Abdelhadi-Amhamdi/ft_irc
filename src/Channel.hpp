/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 17:49:10 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <sys/socket.h>

class Channel {
    private:
        size_t users_limit;
        std::string topic;
        std::string name;
        std::string key;
        std::vector<int> admins;
        std::vector<std::string> modes;
        std::vector<int> invites;
        std::vector<std::pair<int, std::string> > members;
    public:
        Channel(const std::string &channel_name, const std::string &channel_key);
        // Channel(int admin, std::string topic, std::string name);
        void add_user(int fd, const std::string &user, const std::string &channel);
        void ClientResponse(int client_fd, const std::string &username, const std::string &channel_name);
        // void brodcast_msg(std::string msg, std::string &user);
        void brodcast_msg(std::string msg, std::string &user_name, const std::string &channel);
        void setAdmin(int user_fd);
        void setTopic(std::string new_topic);
        const std::string & getTopic() const;
        void setMode(std::string &mode);
        int modeExist_invite_only(const std::string &mode, int user_fd);
        int modeExist_users_limit(const std::string &mode);
        const std::string & getKey() const ;
        ~Channel();
};


