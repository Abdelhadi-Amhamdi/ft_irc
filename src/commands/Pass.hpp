#ifndef Pass_HPP
#define Pass_HPP

#include <sstream>
#include <stdexcept>

#include "../Server.hpp"
class   Server;
class   Connection;

#include "Command.hpp"
#include "../Connection.hpp"

#include <string>
#include <vector>

class Pass : public Command {
    private:
        Connection& executer;

    public:
        Pass(Connection& executer);
        bool    valide();


        void execute(Server& server);
        
};

#endif // Pass_HPP
