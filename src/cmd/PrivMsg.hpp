/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:42:40 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/15 19:07:12 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ACommand.hpp"

class PrivMsg : public ACommand {
    public:
        PrivMsg();
        void exec(std::string &user_infos,std::string &cmd_params, Client &client, Server &server) const;
        ~PrivMsg();
    private:
};
