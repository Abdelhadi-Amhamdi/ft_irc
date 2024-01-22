/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/22 10:20:36 by aamhamdi         ###   ########.fr       */
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
        void setAdmin(const int &user_fd);
        void setMode(const std::string &mode);
        const std::string & getKey() const ;
        
        Channel(const std::string &channel_name, const std::string &channel_key);
        std::string generateMemebrsList(const std::string &username);
        void add_user(const int &fd, const std::string &user);
        void ClientResponse(const int &client_fd, const std::string &username);
        void brodCastMessage(const std::string &message, const std::string &user);
        // int modeExist_users_limit(const std::string &mode);
        // int modeExist_invite_only(const std::string &mode, int user_fd);
        ~Channel();
};


