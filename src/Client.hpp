/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaazouz <nmaazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 02:28:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 17:38:26 by nmaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "color.hpp"
class Connection;

class Client {
	public:
		Client(Connection& connection);
		int getFd() const ;
		const std::string& getLogin() const ;
		const std::string& getNickname() const ;
		const std::string& getRealName() const ;
		const std::string& getHostname() const ;
		const std::vector<std::string>  & getgroupsin() const ;
		bool isRegistred() const ;
		// seters
		void setFd(const int &fd);
		void setgroupsin(const std::string &arg);
		void setIsRegistred();
		void deletefromgroupsin(const std::string &arg);
	private:
		int client_fd;
		const std::string& nick_name;
		const std::string& login;
		std::string real_name;// should add it
		const std::string& hostname;
		bool is_registred;
		std::vector<std::string> groups_in;
};
