/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 02:28:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/20 20:49:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "color.hpp"

class Client {
	public:
		Client(const int &fd, std::string nickname);
		// geters
		int getFd() const ;
		const std::string & getLogin() const ;
		const std::string & getNickname() const ;
		const std::string & getPassword() const ;
		const std::string & getRealName() const ;
		bool isRegistred() const ;
		// seters
		void setFd(const int &fd);
		void setLogin(const std::string &arg);
		void setNickname(const std::string &arg);
		void setPassword(const std::string &arg);
		void setRealName(const std::string &arg);
		void setIsRegistred();
	private:
		int client_fd;
		std::string nick_name;
		std::string password;
		std::string login;
		std::string real_name;
		std::string hostname;
		bool is_registred;
};
