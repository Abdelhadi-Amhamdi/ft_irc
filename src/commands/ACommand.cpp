/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:40:03 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 20:15:42 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

ACommand::ACommand(const std::string& name): name(name) {}

ACommand::~ACommand() {}

void ACommand::commandFormater(const std::string &data) {
    params.clear();
    std::stringstream dataStream(data);
    std::string item;
    dataStream >> item;
    while (dataStream >> item)
      params.push_back(item);
}

std::string  ACommand::get_message(std::string &buffer, std::string &param)
{
    std::string message;
    if (!params.empty()) {
        size_t position = buffer.find(param);
        if (position != std::string::npos)
            message = buffer.substr(position);
    }
	return (message);
}

int ACommand::sendResponse(const std::string &message, int connection_fd) {
    return send(connection_fd, message.c_str(), message.size(), 0);
}
