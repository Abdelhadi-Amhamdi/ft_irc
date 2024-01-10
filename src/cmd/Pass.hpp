/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:26:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/10 12:59:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"

class Pass : public ACommand {
    public:
        Pass();
        void exec(const std::string &pass, Client &cl, Server &c) const;
        ~Pass();
    // private:
    //     std::string name;
};
