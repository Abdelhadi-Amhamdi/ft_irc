/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:26:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 14:04:26 by aamhamdi         ###   ########.fr       */
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
        void exec(const std::string &pass, Client &client, const Server &server) const;
        ~Pass();
};
