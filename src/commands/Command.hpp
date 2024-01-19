#ifndef Command_HPP
#define Command_HPP

#include <string>
#include <vector>
#include <sstream>

class Server;
class Connection;

class Command {
    protected:
        std::string name;
        bool        neadOper;

        std::string prefix;
        std::string command;
        std::string partMessge;
        std::vector<std::string> params;

    public:
        Command(const std::string& name, bool neadOper);
        virtual ~Command();
        virtual void    execute(Server& server) = 0;
        void            getCommand(const std::string& data);
};

#endif // Command_HPP
