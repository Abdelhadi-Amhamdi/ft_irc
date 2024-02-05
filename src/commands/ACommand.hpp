/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:39:20 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/01 18:41:50 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <sstream>
#include <sys/socket.h>

class Server;
class Connection;
class Client;

#include "../Client.hpp"
#include "../Replies.hpp"


class ACommand {
	protected:
		Client						*executer;
		std::string					res_prefix;
		std::string					name;
		std::string                 Messge;
		std::vector<std::string>	params;
	public:
		ACommand(const std::string& name);
		void	commandFormater(const std::string& data);
		static int	sendResponse(const std::string &message, int connection_fd);
		std::string  get_message(std::string &buffer, std::string &params);
		virtual	void Execute(std::string &buffer, Connection &user, Server &server) = 0;
		virtual	~ACommand();
};
