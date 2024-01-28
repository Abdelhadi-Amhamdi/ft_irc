/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:20:09 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/28 09:29:33 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

Client::Client(const int &fd, std::string nickname)
    : client_fd(fd), nick_name(nickname), is_registred(false) {
    start = std::time(NULL);
    struct sockaddr_in cl;
    socklen_t size = sizeof(cl);
    if(getsockname(fd, (struct sockaddr*)&cl, &size) == -1)
        exit (1);
    this->hostname = inet_ntoa(cl.sin_addr);
}

int Client::getFd() const {
    return (client_fd);
}

const std::string & Client::getNickname() const {
    return (nick_name);
}

const std::string Client::getHostname() const {
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

void Client::setNickname(const std::string &arg) {
    this->nick_name = arg;
}

void Client::setLogin(const std::string &arg) {
    this->login = arg;
}
    
void Client::setRealName(const std::string &arg) {
    this->real_name = arg;
}


void Client::setgroupsin(const std::string &arg) {
    this->groups_in.push_back(arg);
}

void Client::setIsRegistred() {
    this->is_registred = true;
}
