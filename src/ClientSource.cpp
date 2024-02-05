/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:09:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/04 13:12:03 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSource.hpp"
#include "Connection.hpp"
#include <cassert>

ClientSource::ClientSource(){}

void            ClientSource::createClient(Connection* connection, const std::string& key) {
    Client  *newClient = new Client(*connection);
    
    clients[key] = newClient;
}

ClientSource& ClientSource::operator=(const ClientSource &c) {
    assert(false);
    if (this != &c) {
        this->clients = c.clients;
    }
    return (*this);
}

void            ClientSource::createClient(Connection* connection) {
    Client  *newClient = new Client(*connection);
    
    clients[connection->getNickname()] = newClient;
}


void ClientSource::deleteClient(const std::string &nickname) {
    std::map<std::string, Client*>::iterator client = clients.find(nickname);
    if (client != clients.end()) {
        delete client->second;
        clients.erase(client);
    }
}

const std::map<std::string,Client*>& ClientSource::getClients() const {
    return (clients);
}

Client* ClientSource::getClientByNickname(const std::string &nickname) {
    std::map<std::string, Client*>::iterator user = clients.find(nickname);
    if (user != clients.end())
        return (user->second);
    return (NULL);
}

size_t ClientSource::getClientsCount() const {
    return (clients.size());
}


ClientSource::~ClientSource(){
    std::map<std::string, Client*>::iterator it = clients.begin();
    for (; it != clients.end(); it++)
        delete it->second;
    clients.clear();
}