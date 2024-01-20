/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:09:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/20 15:51:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSource.hpp"

ClientSource::ClientSource(){}

void ClientSource::createClient(const int fd, const std::string &hostname) {
    Client *new_client = new Client(fd, hostname);

    clients[hostname] = new_client;
}

void ClientSource::deleteClient(const std::string &hostname) {
    std::map<int, Client*>::iterator client = clients.find(hostname);
    if (client != clients.end()) {
        delete client->second;
        clients.erase(client);
    }
}

const std::unordered_map<std::string,Client*>& ClientSource::getClients() const {
    return (clients);
}

ClientSource::~ClientSource(){}