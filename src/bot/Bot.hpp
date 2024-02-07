/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:11:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/07 15:54:03 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// sockets
#include <sys/socket.h>
#include <curl/curl.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>

class Bot {
    private:
        int         index;
        int         bot_fd;
        size_t      port;
        std::string password;
        char        buff[500];
        struct pollfd   fds[1];
        std::vector<std::string> params;
        std::map<std::string,std::pair<std::string, std::string> > manual;
    public:
        Bot(const int &port, const std::string password);
        int     &getindex();
        void    startBot();
        void    manualInit();
        void    dataHandler(std::string data);
        void    initBotSocket(const int &port);
        void    sendResponse(const std::string &message);
        void    manualHelper(const std::string &nickname);
        void    authentification(const std::string &password);
        void    Weather(const std::string &nickname, const std::string &query);
        ~Bot();
};
