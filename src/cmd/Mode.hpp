/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:50:30 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 17:55:38 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include <vector>


class Mode : public ACommand {
    private:
    public:
        Mode();
        void channelHandler(std::string &modes, std::string args);
        void userHandler(std::string &modes);
        void modesFormater(const std::string &modes_string, const std::string &args, std::vector<std::pair<std::string,std::string> > &modes) const;
        void vecGenerator();
        void exec(std::string &user_info, std::string &cmd_params, Client &client, Server &server) const;
        ~Mode();
};
