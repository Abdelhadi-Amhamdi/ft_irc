/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:09:46 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/30 16:10:53 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot() 
	: ACommand("Bot") , prefix(":server_name 001 bot :")
{
	manual["PASS"]    = std::make_pair("- PASS  <password>\r\n", "The PASS command is used to set a 'connection password'\r\n");
	manual["NICK"]    = std::make_pair("- NICK  <nickname>\r\n", "NICK message is used to give user a nickname or change the previous one\r\n");
	manual["USER"]    = std::make_pair("- USER  <login> <hostname> <servername> <realname>\r\n", "The USER message is used to specify the username, hostname, servername and realname of s new user\r\n");
	manual["INVITE"]  = std::make_pair("- INVITE <target> <channel>\r\n", "The INVITE message is used to invite users to a channel\r\n");
	manual["JOIN"]    = std::make_pair("- JOIN  <channel>{,<channel>} [<key>{,<key>}]\r\n", "The JOIN command is used by client to start listening a specific channel\r\n");
	manual["KICK"]    = std::make_pair("- KICK  <channel> <user> [<comment>]\r\n", "The KICK command can be  used  to  forcibly  remove  a  user  from  a channel.\r\n");
	manual["MODE"]    = std::make_pair("- MODE  <channel> <modes> <parameters>\r\n", "The MODE command allows channels to have their mode changed\r\n");
	manual["PART"]    = std::make_pair("- PART  <channel>{,<channel>} <reason>\r\n", "The PART message causes the client to be removed from the given channels\r\n");
	manual["PRIVMSG"] = std::make_pair("- PRIVMSG  <receiver>{,<receiver>} <text to be sent>\r\n", "PRIVMSG is used to send private messages between users\r\n");
	manual["QUIT"]    = std::make_pair("- QUIT [<Quit message>]\r\n", "A client session is ended with a QUIT message\r\n");
	manual["TOPIC"]   = std::make_pair("- TOPIC <channel> [<topic>]\r\n", "The TOPIC message is used to change or view the topic of a channel\r\n");
}

void Bot::Manual(const int &fd) {
	if (params.size() == 1) {
		std::map<std::string,std::pair<std::string, std::string> >::iterator it = manual.begin();
		sendResponse(prefix + "-----manual: -----------\r\n", fd);
		for (; it != manual.end(); it++)
			sendResponse(prefix + it->second.first, fd);
		sendResponse(prefix + "-------------------------\r\n", fd);
	} else if (params.size() == 2) {
		std::map<std::string, std::pair<std::string, std::string> >::iterator it = manual.find(params[1]);
		if (it != manual.end()) {
			sendResponse(prefix + "=> " + it->first + ": -----------\r\n", fd);
			sendResponse(prefix + it->second.first, fd);
			sendResponse(prefix + it->second.second, fd);
			sendResponse(prefix + "----------------------------\r\n", fd);
		}
	}
}

std::string weatherHelper(const std::string &data, const std::string &elm, const std::string &del) {
	std::string ret;
	size_t pos = data.find(elm);
	if (pos == std::string::npos)
		throw std::logic_error("City Not Found... 🙃");
	size_t start = pos + elm.size() + 2;
	size_t end = data.find(del, start);
	if (end == std::string::npos)
		throw std::logic_error("City Not Found... 🙃");
	ret = data.substr(start, end - start);
	return (ret);
}


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void Bot::Weather(const int &fd) {
	data.clear();
	if (params.size() == 2) {
		CURL* curl = curl_easy_init();

		if (curl) {
			std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + params[1] + "&appid=4abf093723c1fcbc5b203ca211f8bb7a";
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
			CURLcode res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				std::cout << "Error\n";
			}

			sendResponse(prefix + "----- Weather⛅: -----------\n", fd);
			try 
			{
				sendResponse(prefix + "City        : " + weatherHelper(data, "name\"", "\"") + "\r\n", fd);
				sendResponse(prefix + "Country     : " + weatherHelper(data, "country\"", "\"") + "\r\n", fd);
				sendResponse(prefix + "Description : " + weatherHelper(data, "description\"", "\"") + "\r\n", fd);
				sendResponse(prefix + "tempuratue  : " + weatherHelper(data, "temp", ",") + "\r\n", fd);
				sendResponse(prefix + "pressure    : " + weatherHelper(data, "pressure", ",") + "\r\n", fd);
				sendResponse(prefix + "visibility  : " + weatherHelper(data, "visibility", ",") + "\r\n", fd);	
			}
			catch (std::exception &e) {
				sendResponse(prefix + e.what() + "\r\n", fd);
			}
			sendResponse(prefix + "--------------------------\n", fd);
			curl_easy_cleanup(curl);
		}		
	}
}

std::string to_string(size_t nb) {
	std::stringstream ss("");
	std::string res;
	ss << nb;
	ss >> res;
	return (res);
}

void Bot::ServerInfos(Server &server, const int &fd) {
	ClientSource &client_manager = server.getClientManager();
	ChannelSource &channel_mnager = server.getChannelManager();
	size_t clients = client_manager.getClientsCount();
	size_t channels = channel_mnager.getChannelsCount();
	sendResponse(prefix + "----- Network Infos: -----------\r\n", fd);
	sendResponse(prefix + "+ clients  : " + to_string(clients) + "\r\n", fd);
	sendResponse(prefix + "+ channels : " + to_string(channels) + "\r\n", fd);
	sendResponse(prefix + "--------------------------------\r\n", fd);
}

void Bot::Execute(std::string &buffer, Connection &user, Server &server) {
	commandFormater(buffer);
	if (params.size() && (params[0] == "help" || params[0] == "HELP")) {
		Manual(user.getFd());
	}
	else if (params.size() && (params[0] == "weather" || params[0] == "WEATHER")) {
		Weather(user.getFd());
	}
	else if (params.size() && (params[0] == "server-infos" || params[0] == "SERVER-INFOS")) {
		ServerInfos(server, user.getFd());
	}
	else {
		sendResponse(prefix + "Hey I'm Bot, How i can help you... 😊\r\n", user.getFd());
		sendResponse(prefix + "-----usage: -----------\r\n", user.getFd());
		sendResponse(prefix + ". BOT help\r\n", user.getFd());
		sendResponse(prefix + ". BOT help <command>\r\n", user.getFd());
		sendResponse(prefix + ". BOT server-infos\r\n", user.getFd());
		sendResponse(prefix + ". BOT weather <city>\r\n", user.getFd());
		sendResponse(prefix + "----------------------\r\n", user.getFd());
	}
}

Bot::~Bot(){}