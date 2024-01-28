/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 02:28:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/28 09:22:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "color.hpp"

class Client {
	public:
		Client(const int &fd, std::string nickname);
		// geters
		int getFd() const ;
		const std::string & getLogin() const ;
		const std::string & getNickname() const ;
		const std::string & getRealName() const ;
		const std::string getHostname() const ;
		const std::vector<std::string>  & getgroupsin() const ;
		bool isRegistred() const ;
		time_t getstart() const {return start;}
		// seters
		void setFd(const int &fd);
		void setLogin(const std::string &arg);
		void setNickname(const std::string &arg);
		void setRealName(const std::string &arg);
		void setgroupsin(const std::string &arg);
		void setIsRegistred();
	private:
		time_t start;
		int client_fd;
		std::string nick_name;
		std::string login;
		std::string real_name;
		std::string hostname;
		bool is_registred;
		std::vector<std::string> groups_in;
};
