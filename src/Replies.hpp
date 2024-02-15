/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:57:07 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/15 10:09:08 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_CHANNELMODEIS(client,ch,modes,args)	("324 " + client + " " + ch + " " + modes + args + "\r\n")
#define RPL_INVITING(client, nick , channel)	("341 " + client + " " + nick + " #" + channel + "\r\n")
#define RPL_NAMESEND(client, channel_name)		("366 " + client + " #" + channel_name + " :End of /NAMES list.\r\n")
#define ERR_NOSUCHNICK(client, nickname)		("401 " + client + " " + nickname + " :No such nick/channel\r\n")
#define ERR_NOSUCHCHANNEL(client, channel)		("403 " + client + " #" + channel + " :No such channel\r\n")
#define ERR_NORECIP(nick)						("411 " + nick + " :No recipient given (PRIVMSG)\r\n")
#define ERR_NOTEXTTOSEND(nick)					("412 " + nick + " :No text to send\r\n")
#define ERR_NONICKNAME(nick)					("431 " + nick + " :No nickname given\r\n")
#define ERR_ERRONNICK(client, nick)				("432 " + client + " " + nick + " :Erroneus nickname\r\n")
#define ERR_ALREADYINUSE(client, nick)			("433 " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_CANNOTSENDTOCHAN(nick, channel)		("404 " + nick + " #" + channel + " :Cannot send to channel\r\n")
#define ERR_USERNOTONCHANNEL(client,nick,chan)	("441 " + client + " " + nick + " #" + chan + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNELL(client, channel)		("442 " + client + " #" + channel + " :You're not on that channel\r\n")
#define ERR_ALREADYONCHANNEL(client,nick, chan)	("443 " + client + " " + nick + " #" + chan + " :is already on channel\r\n")
#define ERR_NEEDMOREPARAMS(client, command)		("461 " + client + " " + command + " : Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED(nick)				("462 " + nick + " :You may not reregister\r\n")
#define ERR_CHANHASLIMIT(client, channel_name)	("471 " + client + " #" + channel_name + " :Cannot join channel (+l)\r\n")
#define ERR_UNKNOWNMODE(client, modechar)		("472 " + client + " " + modechar + " :is unknown mode char to me\r\n")
#define ERR_INVONLYCHANNEL(client, channel)		("473 " + client + " #" + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(client, channel_name)	("475 " + client + " #" + channel_name + " :Cannot join channel (+k)\r\n")
#define ERR_NOTCHANOPER(client, channel)		("482 " + client + " #" + channel + " :You're not channel operator\r\n")

#define RPL_WELCOME(client,network,user,host)	"001 " + client + " :Welcome to the " + network + " Network, " + client + "!" + user + "@" + host + "\r\n"
#define ERR_NOTREGISTERED 						"451 * :You have not registered\r\n"
#define ERR_BADPASS								"464 * :incorrect password\r\n"
#define RPL_NICK(oldNick, newNick) 				":" + oldNick + " NICK " + newNick + "\r\n"
#define RPL_MODE(client, channel, mode, args)	":" + client + " MODE #" + channel + " " + mode + args + "\r\n"
