/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:08:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/29 16:32:56 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Client.hpp"
#include <iostream>
#include <unordered_map>


class ClientSource {
    private:
        std::unordered_map<std::string, Client*>    clients;
    public:
        ClientSource();
        ClientSource&   operator=(const ClientSource &c);
        void            createClient(const int &fd, const std::string &nickname, std::string hostname);
        void            deleteClient(const std::string &nickname);
        const           std::unordered_map<std::string, Client*>& getClients() const;
        Client*         getClientByNickname(const std::string &nickname);
        size_t          getClientsCount() const;
        ~ClientSource();
};
