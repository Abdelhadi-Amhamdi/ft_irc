/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:19:16 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/26 05:41:32 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <curl/curl.h>
#include <stdio.h>

Bot::Bot() 
	: ACommand("Bot") , prefix(":server_name 001 bot :")
{
	manual["PASS"]    = "- PASS : <password>\r\n";
	manual["NICK"]    = "- NICK : <nickname>\r\n";
	manual["USER"]    = "- USER : <login> <hostname> <servername> <realname>\r\n";
	manual["INVITE"]  = "- INVITE : <channel> <target>\r\n";
	manual["JOIN"]    = "- JOIN : <channel_list> <keys_list>\r\n";
	manual["KICK"]    = "- KICK : <channel> <target>\r\n";
	manual["MODE"]    = "- MODE : <channel> <modes> <parameters>\r\n";
	manual["PART"]    = "- PART : <channel> <reason>\r\n";
	manual["PRIVMSG"] = "- PRIVMSG : <target> <message>\r\n";
}

void Bot::Manual(const int &fd) {
	if (params.size() == 1) {
		std::map<std::string,std::string>::iterator it = manual.begin();
		sendResponse(prefix + "-----manual: -----------\r\n", fd);
		for (; it != manual.end(); it++)
			sendResponse(prefix + it->second, fd);
		sendResponse(prefix + "-------------------------\r\n", fd);
	} else {
		std::map<std::string, std::string>::iterator it = manual.find(params[1]);
		if (it != manual.end()) {
			sendResponse(prefix + "-----" + it->first + ": -----------\r\n", fd);
			sendResponse(prefix + it->second, fd);
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
				sendResponse(prefix + "humidity    : " + weatherHelper(data, "humidity", ",") + "\r\n", fd);
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

void Bot::LogTime(Connection &user, Server &server) {
	ClientSource *client_manager = server.getClientManager();
	Client *cl = client_manager->getClientByNickname(user.getNickname());
	if (cl) {
		
		time_t start_time = cl->getstart();
		time_t end_time = std::time(NULL);
		sendResponse(prefix + "----- LogTime: -----------\r\n", user.getFd());
		sendResponse(prefix + "Logtime for " + user.getNickname() + " :" + std::to_string(end_time - start_time) + "s\r\n", user.getFd());
		sendResponse(prefix + "--------------------------\r\n", user.getFd());
	}
}


void Bot::ServerInfos(Server &server, const int &fd) {
	ClientSource *client_manager = server.getClientManager();
	ChannelSource *channel_mnager = server.getChannelManager();
	size_t clients = client_manager->getClientsCount();
	size_t channels = channel_mnager->getChannelsCount();
	sendResponse(prefix + "----- Network Infos: -----------\r\n", fd);
	sendResponse(prefix + "+ clients  : " + std::to_string(clients) + "\r\n", fd);
	sendResponse(prefix + "+ channels : " + std::to_string(channels) + "\r\n", fd);
	sendResponse(prefix + "--------------------------------\r\n", fd);
}

void Bot::Execute(std::string &buffer, Connection &user, Server &server) {
	(void)server;
	params.clear();
	commandFormater(buffer);
	params.erase(params.begin());
	if (params.size() && (params[0] == "help" || params[0] == "HELP")) {
		Manual(user.getFd());
	}
	else if (params.size() && (params[0] == "weather" || params[0] == "WEATHER")) {
		Weather(user.getFd());
	}
	else if (params.size() && (params[0] == "logtime" || params[0] == "LOGTIME")) {
		LogTime(user, server);
	}
	else if (params.size() && (params[0] == "server-infos" || params[0] == "SERVER-INFOS")) {
		ServerInfos(server, user.getFd());
	}
	else {
		sendResponse(prefix + "Hey I'm Bot, How i can help you... 😊\r\n", user.getFd());
		sendResponse(prefix + "-----usage: -----------\r\n", user.getFd());
		sendResponse(prefix + ". bot help\r\n", user.getFd());
		sendResponse(prefix + ". bot help <command>\r\n", user.getFd());
		sendResponse(prefix + ". bot server-infos\r\n", user.getFd());
		sendResponse(prefix + ". bot weather <city>\r\n", user.getFd());
		sendResponse(prefix + ". bot logtime\r\n", user.getFd());
		sendResponse(prefix + "----------------------\r\n", user.getFd());
	}

}

Bot::~Bot(){}