/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:09:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/28 08:51:57 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSource.hpp"

ClientSource::ClientSource(){}

ClientSource& ClientSource::operator=(const ClientSource &c) {
    if (this != &c) {
        this->clients = c.clients;
    }
    return (*this);
}

void ClientSource::createClient(const int &fd, const std::string &nickname) {
    Client *new_client = new Client(fd, nickname);

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

void ClientSource::print() {
    for (std::unordered_map<std::string, Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
        std::cout << it->second->getNickname() << std::endl;
    } 
}

ClientSource::~ClientSource(){}