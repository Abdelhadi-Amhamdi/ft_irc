/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weather.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:16 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 14:41:52 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"


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

void Bot::Weather(const std::string &nickname, const  std::string &query) {
	std::string w_data;
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + query + "&appid=102050dcc5034240d9825e10056d3755";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &w_data);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cout << "Error\n";
            sendResponse("PRIVMSG " + nickname + " :somthing went wrong!\r\n");
            return ;
        }
        sendResponse("PRIVMSG " + nickname + " :----- Weather⛅\r\n");
        try 
        {
            sendResponse("PRIVMSG " + nickname + " :City         " + weatherHelper(w_data, "name\"", "\"") + "\r\n");
            sendResponse("PRIVMSG " + nickname + " :Country      " + weatherHelper(w_data, "country\"", "\"") + "\r\n");
            sendResponse("PRIVMSG " + nickname + " :Description  " + weatherHelper(w_data, "description\"", "\"") + "\r\n");
            sendResponse("PRIVMSG " + nickname + " :tempuratue   " + weatherHelper(w_data, "temp", ",") + "\r\n");
            sendResponse("PRIVMSG " + nickname + " :pressure    : " + weatherHelper(w_data, "pressure", ",") + "\r\n");
            sendResponse("PRIVMSG " + nickname + " :visibility  : " + weatherHelper(w_data, "visibility", ",") + "\r\n");	
        }
        catch (std::exception &e) {
            sendResponse("PRIVMSG " + nickname + " :" + e.what() + "\r\n");
        }
        sendResponse("PRIVMSG " + nickname + " :--------------------------\r\n");
        curl_easy_cleanup(curl);
    }
}


