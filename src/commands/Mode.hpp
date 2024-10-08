/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:08:07 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 21:54:45 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Mode_HPP
#define Mode_HPP

#include <cstddef>
#include <deque>
#include <stdexcept>
#include <string> // Include the header file for the string class
#include <utility>
#include <vector>
#include "../Connection.hpp" // Include the header file for the Connection class
#include "../Server.hpp" // Includez the header file for the Server class
#include "ACommand.hpp"



class Mode : public ACommand {
    private:
        Server&     server;
        Channel*    channel;
        std::string channelName;
        std::string modeString;
        std::deque<std::string> args;

        std::map<char, bool> signs;
        std::vector<std::pair<char, char> > modes;
        std::string valideArgs;


        const   std::string   getArgs();
        void    formate(const std::string& buffer, Connection& user);
        
        void    clear();
        void    exec(char& sign, std::string::iterator& flag, ChannelMode& mode, Connection& user);
        void    setModes(Connection& user);
        void    pushToModes(char sign, char flag);
        
        void    setIMode(char sign, ChannelMode& mode, std::string::iterator& it);
        void    setLMode(char sign, ChannelMode& mode, std::string::iterator& it);
        void    setKMode(char sign, ChannelMode& mode, std::string::iterator& it);
        void    setTMode(char sign, ChannelMode& mode, std::string::iterator& it);
        void    setOMode(char sign, std::string::iterator& flag, Connection& user);

    public:
        Mode(Server& server);
        ~Mode();
        void    Execute(std::string &buffer, Connection &user, Server &server);
};

#endif // Mode_HPP
