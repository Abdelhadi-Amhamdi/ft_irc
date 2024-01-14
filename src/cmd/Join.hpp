/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:55:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 14:22:57 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ACommand.hpp"
#include <vector>
#include "Channel.hpp"
#include "Server.hpp"
#include <sstream>

class Join : public ACommand {
    public:
        Join(const std::string &name);
        void exec(const std::string &value, Client &client, Server &serve) const;
        ~Join();
    private:
};
