/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:48:38 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/24 17:17:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ACommand.hpp"
#include "../Connection.hpp"

class Pass : public ACommand{
    public:
        Pass();
        ~Pass();
        void Execute(std::string &buffer, Connection &user, Server &server);
};


