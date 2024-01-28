#pragma once

#define ERR_NEEDMOREPARAMS\
(client, command) (std::string("461 ") + client + " : " + command + " Not enough parameters\r\n")

#define ERR_CHANOPRIVSNEEDED\
(client, channel) (std::string("482 ") + client + " " + channel + " :You're not channel operator\r\n")

#define ERR_NOSUCHCHANNEL\
(client, channel) (std::string("403 ") + client + " " + channel + " :No such channel\r\n")

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


