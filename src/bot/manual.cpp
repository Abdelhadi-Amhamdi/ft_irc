/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manual.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 18:21:34 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void Bot::manualInit() {
    manual["PASS"]    = std::make_pair("- PASS  <password>\r\n", "-> The PASS command is used to set a 'connection password'\r\n");
	manual["NICK"]    = std::make_pair("- NICK  <nickname>\r\n", "-> NICK message is used to give user a nickname or change the previous one\r\n");
	manual["USER"]    = std::make_pair("- USER  <login> <hostname> <servername> <realname>\r\n", "-> The USER message is used to specify the username, hostname, servername and realname of s new user\r\n");
	manual["INVITE"]  = std::make_pair("- INVITE <target> <channel>\r\n", "-> The INVITE message is used to invite users to a channel\r\n");
	manual["JOIN"]    = std::make_pair("- JOIN  <channel>{,<channel>} [<key>{,<key>}]\r\n", "-> The JOIN command is used by client to start listening a specific channel\r\n");
	manual["KICK"]    = std::make_pair("- KICK  <channel> <user> [<comment>]\r\n", "-> The KICK command can be  used  to  forcibly  remove  a  user  from  a channel.\r\n");
	manual["MODE"]    = std::make_pair("- MODE  <channel> <modes> <parameters>\r\n", "-> The MODE command allows channels to have their mode changed\r\n");
	manual["PART"]    = std::make_pair("- PART  <channel>{,<channel>} <reason>\r\n", "-> The PART message causes the client to be removed from the given channels\r\n");
	manual["PRIVMSG"] = std::make_pair("- PRIVMSG  <receiver>{,<receiver>} <text to be sent>\r\n", "-> PRIVMSG is used to send private messages between users\r\n");
	manual["QUIT"]    = std::make_pair("- QUIT [<Quit message>]\r\n", "-> A client session is ended with a QUIT message\r\n");
	manual["TOPIC"]   = std::make_pair("- TOPIC <channel> [<topic>]\r\n", "-> The TOPIC message is used to change or view the topic of a channel\r\n");
}

void Bot::manualHelper(const std::string &nickname) {
	if (params.size() > 1){
		std::map<std::string, std::pair<std::string, std::string> >::iterator it = manual.find(params[1]);
		if (it != manual.end()) {
			sendResponse("PRIVMSG " + nickname + " " + it->second.first + "\r\n" + "PRIVMSG " + nickname + " " + it->second.second + "\r\n");
		}	
	}
	else {
		std::string ret;
		std::map<std::string, std::pair<std::string, std::string> >::iterator it = manual.begin();
		for (; it != manual.end(); it++) {
			ret += "PRIVMSG " + nickname + " " + it->second.first + "\r\n";
			ret += "PRIVMSG " + nickname + " " + it->second.second + "\r\n";
		}
		sendResponse(ret);
	}
}
