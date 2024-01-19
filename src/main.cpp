/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:19:59 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/17 22:04:04 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void _error(std::string msg) {
	std::cerr << msg << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3)
		return (_error("Error: inalid args, usage: (./ircserv <port> <password>)!"), 1);
    
    try {
    Server serv(argv[2], std::stoi(argv[1]));
        serv.start_server();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}