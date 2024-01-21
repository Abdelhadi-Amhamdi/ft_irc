/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:20:09 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 12:58:29 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(const int &fd, std::string nickname)
    : client_fd(fd), nick_name(nickname), is_registred(false) {}

int Client::getFd() const {
    return (client_fd);
}

const std::string & Client::getNickname() const {
    return (nick_name);
}

const std::string & Client::getHostname() const {
    return (hostname);
}

const std::string & Client::getLogin() const {
    return (login);
}

const std::string & Client::getRealName() const {
    return (real_name);
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

void Client::setHostname(const std::string &arg) {
    this->hostname = arg;
}

void Client::setIsRegistred() {
    this->is_registred = true;
}
