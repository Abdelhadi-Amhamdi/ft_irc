/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:22:21 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/21 17:12:15 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "ACommand.hpp"
#include "../Server.hpp"

template<typename I, typename F>
void for_each(I begin, I end, F func) {
    for(I it = begin ; it != end; it++)
        func(it);
}

class Join : public ACommand {
    private:
        std::vector<std::pair<std::string, std::string> > channels;
    public:
        Join();
        void channels_formater();
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Join();
};
