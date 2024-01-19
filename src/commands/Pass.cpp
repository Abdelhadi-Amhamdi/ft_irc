#include "Pass.hpp"

// Pass::Pass(Connection& executer)
//     : Command("PASS", false), executer(executer)
// {
    
// }

Pass::Pass(Connection& executer)
    : Command("PASS", false), executer(executer)

{}

bool    Pass::valide()
{
    if (params.empty())
    {
        std::cout << "invalid argument.\n";
        return false;
    }
    return true;
}

void Pass::execute(Server& server)
{
    if (executer.getIsConnected() == true)
    {
        std::cout << executer.getFd() << " is already connected.\n";
        return;
    }
    this->getCommand(executer.getBuffer());
    
    if (valide() == false)
        return;
    if (!params.empty() && this->params[0] == server.getPassword())
    {
        executer.setIsConnected(true);
        std::cout << executer.getFd() << " hase connected.\n";
    }
    else {
        std::cout << "bad password\n";
    }
}
