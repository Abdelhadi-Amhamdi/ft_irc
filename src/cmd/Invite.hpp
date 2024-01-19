/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:04:35 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 10:06:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ACommand.hpp"

class Invite : public ACommand {
    public:
        Invite();
        void exec(std::string &user_info, std::string &cmd_prams, Client &client, Server &server) const;
        ~Invite();
    private:
};
