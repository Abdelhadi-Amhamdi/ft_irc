#pragma once


// invite command
#define ERR_NOSUCHNICKK(client, nickname)(":server_name 401 " + client + " " + nickname + " :No such nick/channel\r\n")

#define ERR_ALREADYONCHANNEL(nick, arg)(":server_name 443 " + nick + " #" + arg + " :is already on channel\r\n")

#define RPL_INVITING(nick, reciver , channel) (":server_name 341 " + nick + " " + reciver + " #" + channel + "\r\n")



// join command

#define ERR_NEEDMOREPARAMSS\
(client, command) (":server_name 461 " + client + " :" + command + ": Not enough parameters\r\n")

#define RPL_NAMESEND\
(client, channel_name) (":server_name 366 " + client + " " + channel_name + " :End of /NAMES list.\r\n")

#define ERR_CHANHASLIMIT\
(client, channel_name) (":server_name 471 " + client + " #" + channel_name + " :Cannot join channel (+l)\r\n")

#define ERR_INVONLYCHANNEL\
(client, channel_name) (":server_name 437 " + client + " #" + channel_name + " :Cannot join channel (+i)\r\n")

#define ERR_BADCHANNELKEY\
(client, channel_name) (":server_name 475 " + client + " #" + channel_name + " :Cannot join channel (+k)\r\n")


// kick command

#define ERR_NOTONCHANNELL\
(client, channel) (":server_name 442 " + client + " #" + channel + " :You're not on that channel\r\n")

#define ERR_NOTCHANOPER\
(client, channel) (":server_name 482 " + client + " #" + channel + " :You're not channel operator\r\n")


#define ERR_USERNOTONCHANNEL\
(client, channel) (":server_name 441 " + client + " #" + channel + " :They aren't on that channel\r\n")


// nick command

#define ERR_NONICKNAME\
(client) (":server_name 431 " + client + " :No nickname given\r\n")

#define ERR_ERRONNICK\
(client) (":server_name 432 " + client + " :Erroneus nickname\r\n")

#define ERR_ALREADYINUSE\
(client) (":server_name 433 " + client + " :Nickname is already in use\r\n")


// part command


#define ERR_NOSUCHCHANNELL\
(client, channel) (":server_name 403 " + client + " :" + channel + " :No such channel\r\n")


// pass command

#define ERR_BADPASS ":server_name 464 nick :No nickname given\r\n"

#define ERR_ALREADYREGISTRED\
(nick) (":server_name 462 " + nick + " :You may not reregister\r\n")

// privmsg command

#define ERR_NORECIP\
(nick) (":server_name 411 " + nick + " :No recipient given (PRIVMSG)\r\n")

#define ERR_NOTEXTTOSEND\
(nick) (":server_name 412 " + nick + " :No text to send\r\n")

#define ERR_CANNOTSENDTOCHAN\
(nick, channel) (":server_name 404 " + nick + " #" + channel + " :Cannot send to channel\r\n")






#define ERR_NEEDMOREPARAMS\
(client, command) ":server_name " + (std::string("461 ") + client + " :" + command + ": Not enough parameters\r\n")

#define ERR_CHANOPRIVSNEEDED\
(client, channel) ":server_name " + (std::string("482 ") + client + " :" + channel + " :You're not channel operator\r\n")

#define ERR_NOSUCHCHANNEL\
(client, channel) ":server_name " + (std::string("403 ") + client + " :" + channel + " :No such channel\r\n")

#define ERR_UMODEUNKNOWNFLAG\
(client)(std::string("501 ") + client + " :Unknown MODE flag\r\n")

#define ERR_UNKNOWNMODE\
(client, modechar) (std::string("472") + client + " " + modechar + " :is unknown mode char to me\r\n")

#define ERR_USERNOTINCHANNEL\
(client, nick, channel) (std::string("441 ") + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")

#define ERR_NOSUCHNICK\
(client, nickname)(std::string("401 ") + client + " " + nickname + " :No such nick/channel\r\n")

#define RPL_INVITELIST()

#define RPL_MODE(client, channel, mode, args) ":" + client + " MODE #" + channel + " " + mode + args + "\r\n"


#define RPL_CHANNELMODEIS\
(client, channel, modestring, arguments) (std::string("324 ") + client + " " + channel + " " + modestring + arguments + "\r\n")


