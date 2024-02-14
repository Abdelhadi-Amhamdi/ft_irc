/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:08:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/14 20:19:08 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Client.hpp"
#include <iostream>
#include <map>


class ClientSource {
    private:
        std::map<std::string, Client*>    clients;
        ClientSource&   operator=(const ClientSource &c);
        ClientSource(const ClientSource &c);
        
    public:
        ClientSource();
        void            createClient(Connection* connection, const std::string& key);
        void            createClient(Connection* connection);
        void            createClient(const int &fd, const std::string &nickname, std::string hostname);
        void            deleteClient(const std::string &nickname);
        const           std::map<std::string, Client*>& getClients() const;
        Client*         getClientByNickname(const std::string &nickname);
        size_t          getClientsCount() const;
        ~ClientSource();
};
