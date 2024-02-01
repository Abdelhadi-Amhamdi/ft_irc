/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:09:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/31 17:58:56 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSource.hpp"
#include "Connection.hpp"
#include <cassert>

ClientSource::ClientSource(){}

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

void ClientSource::createClient(const int &fd, const std::string &nickname, std::string sfd) {
    Client *new_client = new Client(fd, nickname, sfd);

    clients[nickname] = new_client; 
}

void ClientSource::deleteClient(const std::string &nickname) {
    std::unordered_map<std::string, Client*>::iterator client = clients.find(nickname);
    if (client != clients.end()) {
        delete client->second;
        clients.erase(client);
    }
}

const std::unordered_map<std::string,Client*>& ClientSource::getClients() const {
    return (clients);
}

Client* ClientSource::getClientByNickname(const std::string &nickname) {
    std::unordered_map<std::string, Client*>::iterator user = clients.find(nickname);
    if (user != clients.end())
        return (user->second);
    return (NULL);
}

size_t ClientSource::getClientsCount() const {
    return (clients.size());
}


ClientSource::~ClientSource(){
    std::unordered_map<std::string, Client*>::iterator it = clients.begin();
    for (; it != clients.end(); it++)
        delete it->second;
    clients.clear();
}