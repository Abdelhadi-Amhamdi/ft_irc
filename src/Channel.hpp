/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:14:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/09 00:27:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>

class Channel {
    public:
        Channel(int admin, std::string topic, std::string name);
        void add_user(int fd, std::string nickname);
        void brodcast_msg(std::string msg);
        ~Channel();
    private:
        std::string topic;
        std::string channel_name;
        int admin_fd;
        std::vector<int> members;
};
