/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/14 21:36:22 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ACommand.hpp"
#include <map>
#include "../Client.hpp"



class Nick : public ACommand {
    public:
        Nick();
        void exec(std::string &user_infos, std::string &cmd_params, Client &clients, Server &server) const;
        ~Nick();
    private:
};
