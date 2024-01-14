/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:08:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:18:43 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Client.hpp"
#include <iostream>
#include <map>

class Match_nickname {
    std::string value;
    public:
        Match_nickname(std::string nick) : value(nick) {} 
        bool operator()(const std::pair<int, Client*> &cl) const {
            return (cl.second->getNickname() == value);
        } 
};

class ClientSource {
    public:
        ClientSource();
        void createClient(int fd, std::string &hostname);
        Client* getClient(int fd);
        void deleteClient(int fd);
        bool checkNickName(const std::string &name);
        ~ClientSource();
    private:
        std::map<int, Client*> clients;
};
