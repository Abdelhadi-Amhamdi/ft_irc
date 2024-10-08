/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:39:04 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/07 16:02:03 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
int *botloop = NULL;

int parsePort(std::string port, std::string password) {
    if (password.empty()) {
        std::cerr << "Error: empty password!\n";    
        return (-1);
    }
    for (size_t index = 0; index < password.size(); index++) {
        if (std::isspace(password[index])) {
            std::cerr << "Error: invalid password!\n";
            return (-1);
        }
    }
    for (size_t i = 0; i < port.size(); i++) {
        if (!std::isdigit(port[i]))
        {
            std::cerr << "Error: invalid character on port number!\n";    
            return (-1);
        }
    }
    int ret_port;
    std::stringstream portStream(port);
    portStream >> ret_port;
    if (ret_port < 0 || ret_port > 65535) {
        std::cerr << "Error: port out of range!\n";
        return (-1);
    }
    return (ret_port);
}

void signal_handler(int sig_type) {
    (void)sig_type;
    if (botloop != NULL)
        *botloop = 0;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    if (argc != 3) {
        std::cerr << "Error: inalid args, usage: (./bot <port> <password>)!\n";
        return (1);
    }
    int port = parsePort(argv[1], argv[2]);
    if (port == -1)
        return (1);
    try {
        Bot bot(port, argv[2]);
        botloop = &bot.getindex();
        bot.startBot(); 
    } 
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}