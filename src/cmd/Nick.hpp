/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 13:24:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ACommand.hpp"
#include <map>
#include "../Client.hpp"

class Match_nickname {
    std::string value;
    public:
        Match_nickname(std::string nick) : value(nick) {} 
        bool operator()(const std::pair<int, Client*> &cl) const {
            return (cl.second->getNickname() == value);
        } 
};

class Nick : public ACommand {
    public:
        Nick();
        void exec(const std::string &value, Client &cl, Server &sr) const;
        ~Nick();
    private:
};
