/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 14:18:07 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>

class Channel {
    public:
        Channel() {}
        // Channel(int admin, std::string topic, std::string name);
        void add_user(int fd, const std::string &user, const std::string &channel);
        void setadmin(int fd);
        void brodcast_msg(std::string msg);
        ~Channel();
    private:
        std::string topic;
        std::string channel_name;
        int admin_fd;
        std::vector<std::pair<int, std::string> > members;
};
