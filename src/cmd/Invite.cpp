/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:04:38 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 11:26:22 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

Invite::Invite(){}


void Invite::exec(std::string &user_info, std::string &cmd_params, Client &client, Server &server) const {
    (void)user_info;
    (void) cmd_params;
    (void) client;
    (void) server;
    // std::string nickname,channelname;

    // std::stringstream paramsStream(cmd_params);

    // paramsStream >> nickname;
    // paramsStream >> channelname;

    // Client *user_to_invite = server.getUserInfos(nickname);
    // server.inviteUserToChannel();

}

Invite::~Invite(){}
