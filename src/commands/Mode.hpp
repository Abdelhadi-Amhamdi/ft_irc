#ifndef Mode_HPP
#define Mode_HPP

#include <cstddef>
#include <stdexcept>
#include <string> // Include the header file for the string class
#include <sys/_types/_size_t.h>
#include <utility>
#include <vector>
#include "../Connection.hpp" // Include the header file for the Connection class
#include "../Server.hpp" // Includez the header file for the Server class
#include "ACommand.hpp"



class Mode : public ACommand {
    private:
        Channel*    channel;
        // Connection& executer;
        // std::vector<std::pair<std::string, std::string>> flags;

    public:
        Mode();
        ~Mode();
        void    exec(char sign, char flag, int& indexKey);
        void    Execute(std::string &buffer, Connection &user, Server &server);
};

#endif // Mode_HPP
