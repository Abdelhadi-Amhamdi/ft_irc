/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:50:33 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/19 18:19:18 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

Mode::Mode(){}

void Mode::channelHandler(std::string &modes, Client &client, Server &server) {
    
}

void Mode::userHandler(std::string &modes) {
    (void)modes;
}

void Mode::modesFormater(const std::string &modes_string, const std::string &args, std::vector<std::pair<std::string,std::string> > &modes) const {
    std::stringstream argsStream(args);
    std::string modes_set = "oltki";
    char sign = '\0';
    
    for (size_t i = 0; i < modes_string.size(); i++) {
        if (modes_string[i] == '-' || modes_string[i] == '+') {
            sign = modes_string[i];   
        }
        else if (modes_set.find(modes_string[i]) != std::string::npos && sign) {
            std::string second,first;
            if (modes_string[i] == 'o' || modes_string[i] == 'l' || modes_string[i] == 'k')
                argsStream >> second;
            first += sign;
            first += modes_string[i];
            std::pair<std::string, std::string> item = std::make_pair(first,second);
            modes.push_back(item);
        } else
            throw std::logic_error("invalid mode");
    }
}

void Mode::exec(std::string &user_info, std::string &cmd_params, Client &client, Server &server) const {
    (void)user_info;
    std::string target,modes,argumments,elm;
    std::stringstream paramsStream(cmd_params);
    std::vector<std::pair<std::string,std::string> > modes_vector;

    paramsStream >> target;
    paramsStream >> modes;
    paramsStream >> argumments;
    while (paramsStream >> elm) {
        argumments += " ";
        argumments += elm;
    }
    try {
        modesFormater(modes,argumments, modes_vector);
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
        return ;
    }
    if (target.find("#") != std::string::npos)
        channelHandler(modes, client, server);
    // else
    //     userHandler(modes);
}

Mode::~Mode(){}