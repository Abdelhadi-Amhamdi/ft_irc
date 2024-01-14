/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:09:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 09:59:41 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSource.hpp"

ClientSource::ClientSource(){}

void ClientSource::createClient(int fd) {
    Client *new_client = new Client(fd);

    clients[fd] = new_client;
}

void ClientSource::deleteClient(int fd) {
    std::map<int, Client*>::iterator client = clients.find(fd);
    if (client != clients.end()) {
        delete client->second;
        clients.erase(client);
    }
}

Client* ClientSource::getClient(int fd) const {
    std::map<int, Client*>::iterator client = clients.find(fd);
    if (client == clients.end())
        return (NULL);
    return (client->second);
}

ClientSource::~ClientSource(){}