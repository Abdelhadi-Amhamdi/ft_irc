#include "Mode.hpp"

Mode::Mode()
    : ACommand("MODE")
{
    
}
Mode::~Mode()
{
    
}
bool    isFlag(char c)
{
    return c == 'i' || c == 't' || c == 'k' || c == 'o' ||c == 'l';
}

void    Mode::exec(char sign, char flag, int& indexKey)
{
    ChannelMode mode = channel->getMode();
    switch (flag) {
        case 'i':
            mode.setInvitOnly(sign);
            break;
        case 'l':
            mode.setLimit(sign, params[indexKey++]);
            break;
        case 'k':
            mode.setKey(params[indexKey++]);
            break;
        case 't':
            mode.setTopic(sign);
            break;
        default:
            std::cout << __LINE__ << "DEFAULT\n";
    }
}

void Mode::Execute(std::string &buffer, Connection &user, Server &server)
{
    (void) user;
    commandFormater(buffer);
    userInfosChecker();
    if (params[0][0] == '#')
        params[0].erase(params[0].begin());
    channel = server.getChannelManager()->getChannelByName(params[0]);
    if (channel == NULL)
    {
        std::cout << "no such channel\n";
        return ;
    }
    
    int indexKey = 2;  
    std::string flags = params[1];
    char sign = 0;
    size_t i = 0;
    if (flags[i] == '+' || flags[i] == '-')
        sign = flags[i];
    for (++i; i < flags.size(); i++) {
        if (isFlag(flags[i]))
        {
            exec(sign, flags[i], indexKey);
        }
    }
}


