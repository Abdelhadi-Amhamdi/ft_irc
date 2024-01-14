/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:09:11 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:18:57 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSource.hpp"

ClientSource::ClientSource(){}

void ClientSource::createClient(int fd, std::string &hostname) {
    Client *new_client = new Client(fd, hostname);

    clients[fd] = new_client;
}

void ClientSource::deleteClient(int fd) {
    std::map<int, Client*>::iterator client = clients.find(fd);
    if (client != clients.end()) {
        delete client->second;
        clients.erase(client);
    }
}

Client* ClientSource::getClient(int fd) {
    std::map<int, Client*>::iterator client = clients.find(fd);
    if (client == clients.end())
        return (NULL);
    return (client->second);
}

bool ClientSource::checkNickName(const std::string &name) {
    std::map<int, Client*>::iterator user = std::find_if(clients.begin(), clients.end(), Match_nickname(name));
    if (user != clients.end())
        return (false);
    return (true);
}

ClientSource::~ClientSource(){}