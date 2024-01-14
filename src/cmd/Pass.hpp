/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:26:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:36:50 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"

class Pass : public ACommand {
    public:
        class BADPASS : public std::exception {
            const char *what() const throw () {
                return ("Error: client auth failed, invalid password!");
            }
        };
        Pass();
        void exec(std::string &user_infos, std::string &cmd_params, Client &client, Server &server) const;
        ~Pass();
};
