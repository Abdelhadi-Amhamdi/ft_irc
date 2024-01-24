/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 22:32:36 by aamhamdi         ###   ########.fr       */
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
        std::vector<int> invites;
        std::vector<std::string> modes;
        std::vector<std::pair<int, std::string> > members;
    public:
        size_t  getMembersCount() const;
        const   std::string &getName() const ;
        void    addAdmin(const int &user_fd);
        void    delAdmin(const int &user_fd);
        const   std::string & getKey() const ;
        void    setMode(const std::string &mode);
        
        Channel(const std::string &channel_name, const std::string &channel_key);
        std::string generateMemebrsList();
        bool    checkIfAdmin(const int &user_fd);
        void    delUserFromChannel(const int &fd);
        void    addUserToChannel(const int &fd, const std::string &user);
        void    brodCastMessage(const std::string &message, const std::string &user);
        void    broadCastResponse(const std::string &message);
        ~Channel();
};


