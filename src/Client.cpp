/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:20:09 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/07 16:19:47 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "Connection.hpp"

Client::Client(Connection& connection)
	: client_fd(connection.getFd()),
	  nick_name(connection.getNickname()),
	  login(connection.getUser()),
	  hostname(connection.getHostname()) {}

int Client::getFd() const {
    return (client_fd);
}

const std::string & Client::getNickname() const {
    return (nick_name);
}

const std::string& Client::getHostname() const {
    return (hostname);
}

const std::string & Client::getLogin() const {
    return (login);
}

const std::string & Client::getRealName() const {
    return (real_name);
}
const std::vector<std::string> & Client::getgroupsin() const {
    return (groups_in);
}

bool Client::isRegistred() const {
    return this->is_registred;
}

void Client::setFd(const int &fd) {
    this->client_fd = fd;
}

void Client::setgroupsin(const std::string &arg) {
    this->groups_in.push_back(arg);
}

void Client::deletefromgroupsin(const std::string &arg) {
    const std::vector<std::string>::iterator it = std::find(groups_in.begin(), groups_in.end(), arg);
    if (it != groups_in.end()) {
        groups_in.erase(it);
    }
}

void Client::setIsRegistred() {
    this->is_registred = true;
}
