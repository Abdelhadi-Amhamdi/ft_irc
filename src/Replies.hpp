#pragma once

#define ERR_NEEDMOREPARAMS\
(client, command) (std::string("461 ") + client + " : " + command + " Not enough parameters\r\n")

#define ERR_NOSUCHCHANNEL\
(client, channel) (std::string("403 ") + client + " " + channel + " :No such channel\r\n")

#define RPL_INVITELIST()

#define RPL_MODE(client, channel, mode, args) ":" + client + " MODE #" + channel + " " + mode + args + "\r\n"


#define RPL_CHANNELMODEIS\
(client, channel, modestring, arguments) (std::string("324 ") + client + " " + channel + " " + modestring + arguments + "\r\n")