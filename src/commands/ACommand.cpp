/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:40:03 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 12:40:45 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

ACommand::ACommand(const std::string& name): name(name) {}

ACommand::~ACommand() {}

void ACommand::commandFormater(const std::string &data) {
    std::stringstream dataStream(data);
    std::string item;
    while (dataStream >> item)
      params.push_back(item);
}

void ACommand::userInfosChecker() {
    if (params[0][0] == ':')
    {
        // check data;
        params.erase(params.begin());
    }
    params.erase(params.begin());
}

void ACommand::sendResponse(const std::string &message, int connection_fd) {
    send(connection_fd, message.c_str(), message.size(), 0);
}
