/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:22:21 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/23 23:14:31 by kben-ham         ###   ########.fr       */
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
