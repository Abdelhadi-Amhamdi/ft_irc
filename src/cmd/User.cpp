/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:02:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 16:13:58 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(){}

void User::exec(std::string &user_infos,std::string &cmd_params, Client &client, Server &server) const {
    (void)user_infos;
    (void)client;
    (void)server;
    std::string username,hostname,servername,realname;
    std::stringstream dataStream(cmd_params);

    dataStream >> username;
    dataStream >> hostname;
    dataStream >> servername;
    dataStream >> realname;
    std::string item;
    while (dataStream >> item) {
        realname += " ";
        realname += item;
    }
    //std::cout << username << "|" << hostname << "|" << servername << "|" << realname << std::endl;
}

User::~User(){}