/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:56:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/18 18:10:07 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join() {}


//    *ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//    *ERR_INVITEONLYCHAN              *ERR_BADCHANNELKEY
//    *ERR_CHANNELISFULL               ERR_BADCHANMASK
//    ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//    RPL_TOPIC

void Join::join_response(int client_fd, const std::string &username, const std::string &response) const {
    (void)username;
    send(client_fd, response.c_str(), response.size(), 0);
}

void Join::channels_formater(std::string &data, std::vector<std::pair<std::string, std::string> > &channels) const {
   
    std::string channels_list, keys_list;
    std::stringstream ss(data);
    ss >> channels_list;
    ss >> keys_list;
    
    std::stringstream channelsStream(channels_list);
    std::stringstream keysStream(keys_list);
    std::string item;
    
    while (std::getline(channelsStream, item, ',')) {
        std::string key;
        std::getline(keysStream, key, ',');
        if (!item.empty() && item[0] == '#') {
            item.erase(item.begin());
            if (item.empty()) {
                channels.clear();   
                return ;
            }
        }
        std::pair<std::string, std::string> elm = std::make_pair(item, key);
        channels.push_back(elm);
    }
}

void Join::exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &server) const {
    (void)user_infos;
    std::vector<std::pair<std::string, std::string> > channels;
    channels_formater(cmd_params, channels);
    if (channels.empty()) {
        join_response(client.getFd(), client.getNickname(), ERR_NEEDMOREPARAMS);
        return; 
    }
    try {
        for (size_t i = 0; i < channels.size(); i++)
            server.addUserToChannel(channels[i].first, channels[i].second, client.getFd(), client.getNickname()); 
    }
    catch (std::exception &e) {
        std::cout << RED << e.what() << RESET << std::endl;
        if (!strcmp(e.what(), "ERR_INVITEONLYCHAN"))
            join_response(client.getFd(), client.getNickname(), ERR_INVITEONLYCHAN);
        else if (!strcmp(e.what(), "ERR_CHANNELISFULL"))
            join_response(client.getFd(), client.getNickname(), ERR_CHANNELISFULL);
        else if (!strcmp(e.what(), "ERR_BADCHANNELKEY"))
            join_response(client.getFd(), client.getNickname(), ERR_BADCHANNELKEY);
    }
}

Join::~Join(){}