

#pragma once
#include <iostream>
#include "ACommand.hpp"
#include "../Server.hpp"
#include <map>

class Bot : public ACommand {
    private:
        std::string data;
        const std::string prefix;
        std::map<std::string,std::string> manual;
    public:
        Bot();
        void Manual(const int &fd);
        void Weather(const int &fd);
        void LogTime(Connection &user, Server &server);
        void ServerInfos(Server &server, const int &fd);
        void Execute(std::string &buffer, Connection &user, Server &server);
        ~Bot();
};
