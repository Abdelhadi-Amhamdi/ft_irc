/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 02:28:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/09 01:04:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "color.hpp"

class Client {

	public :
		Client() : logedin(false) {}
		Client(int fd) : fd(fd), logedin(false) {}
		int getFd() const ;
		const std::string & getLogin() const ;
		const std::string & getNickname() const ;
		const std::string & getPassword() const ;
		const std::string & getRealName() const ;
		bool islogedin() const ;

		void setFd(int arg);
		void setLogin(const std::string &arg);
		void setNickname(const std::string &arg);
		void setPassword(const std::string &arg);
		void setRealName(const std::string &arg);
		void setlogedin();
	private:
		int fd;
		std::string nickname;
		std::string password;
		std::string login;
		std::string real_name;
		bool logedin;
};