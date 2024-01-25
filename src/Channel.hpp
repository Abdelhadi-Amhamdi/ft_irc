/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/25 20:50:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ChannelMode.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <map>


// +n by default means that user should join in order to talk

class Channel {
    private:
        std::string topic;
        std::string name;
        std::vector<int> admins;
        std::vector<int> invites;
        ChannelMode mode;
        std::map<int, std::string> members;
    public:
        size_t  getMembersCount() const;
        void    addInvite(const int &user_fd);
        void    addAdmin(const int &user_fd);
        void    delAdmin(const int &user_fd);
        const ChannelMode& getMode() const;
        const   std::string &getName() const ;
        const   std::string &getTopic() const;
        void    setTopic(const std::string &topic);
        
        
        Channel(const std::string &channel_name, const std::string &channel_key);
        std::string generateMemebrsList();
        bool    isMemberInChannel(const int &fd);
        bool    checkIfAdmin(const int &user_fd);
        bool    checkIfInvited(const int &user_fd);
        void    delUserFromChannel(const int &fd);
        void    addUserToChannel(const int &fd, const std::string &user);
        void    brodCastMessage(const std::string &message, const std::string &user);
        void    broadCastResponse(const std::string &message);
        ~Channel();
};


