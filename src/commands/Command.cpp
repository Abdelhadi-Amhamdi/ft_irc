#include "Command.hpp"

Command::Command(const std::string& name, bool neadOper)
    : name(name), neadOper(neadOper)
{
    
}

Command::~Command()
{}

void            Command::getCommand(const std::string& data)
{
    std::stringstream   ss(data);

    if (data[0] == ':')
    {
        ss >> prefix;
        prefix.erase(0, 1);
    }

    ss >> command;

    std::string tmp;
    while (ss >> tmp && tmp[0] != ':')
        params.push_back(tmp);
    
    if (tmp[0] == ':')
    {
        tmp.erase(0, 1);
        partMessge += tmp;
        while (ss >> tmp) {
            partMessge += " " + tmp;
        }
    }
}
