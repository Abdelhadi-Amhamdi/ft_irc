/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSource.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:08:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/20 15:49:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Client.hpp"
#include <iostream>
#include <unordered_map>


class ClientSource {
    private:
        std::unordered_map<std::string, Client*>    clients;
    public:
        ClientSource();
        void createClient(int fd, std::string &hostname);
        void deleteClient(std::string &nickname);
        const std::unordered_map<std::string, Client*>& getClients() const;
        ~ClientSource();
};
