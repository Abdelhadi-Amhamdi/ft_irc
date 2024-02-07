/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:19:59 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/07 16:23:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int *g_index = NULL;

void signalHandler(int sig_type) {
    (void)sig_type;
    if (g_index)
        *g_index = 0;
}

int parse(std::string port_input, std::string pass_input, int &port, std::string &pass) {
    if (pass_input.empty()) {
        std::cerr << "Error: empty password!\n";    
        return (1);
    }
    size_t index = 0;
    for (; index < pass_input.size(); index++) {
        if (std::isspace(pass_input[index])) {
            std::cerr << "Error: invalid password!\n";
            return (1);
        }
    }
    
    pass = pass_input;
    for (size_t i = 0; i < port_input.size(); i++) {
        if (!std::isdigit(port_input[i])) {
            std::cerr << "Error: invalid character on port number!\n";    
            return (1);
        }
    }
    std::stringstream portStream(port_input);
    portStream >> port;
    if (port < 0 || port > 65535) {
        std::cerr << "Error: port out of range!\n";
        return (1);
    }
    return (0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    int port;
    std::string password;
    if (argc != 3)
    {
        std::cerr << "Error: inalid args, usage: (./ircserv <port> <password>)!\n";
        return (1);
    }
    if (parse(argv[1], argv[2], port, password))
        return (1);
    try {
        Server serv(password, port);
        g_index = &serv.getIndex();
        serv.start_server();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}