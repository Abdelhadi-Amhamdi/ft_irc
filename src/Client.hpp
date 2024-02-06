/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 02:28:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 21:57:57 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
class Connection;

class Client {
	private:
		int							client_fd;
		bool						is_registred;
		std::string					real_name;
		const std::string&			nick_name;
		const std::string&			login;
		const std::string&			hostname;
		std::vector<std::string>	groups_in;
	public:
		Client(Connection& connection);
		int		getFd() const ;
		const	std::string& getLogin() const ;
		const	std::string& getNickname() const ;
		const	std::string& getRealName() const ;
		const	std::string& getHostname() const ;
		const	std::vector<std::string>  & getgroupsin() const ;
		void	setIsRegistred();
		bool	isRegistred() const ;
		void	setFd(const int &fd);
		void	setgroupsin(const std::string &arg);
		void	deletefromgroupsin(const std::string &arg);
};
