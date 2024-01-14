/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:55:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:36:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ACommand.hpp"
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"
#include <sstream>

class Join : public ACommand {
    public:
        Join();
        void exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &serve) const;
        ~Join();
    private:
};
