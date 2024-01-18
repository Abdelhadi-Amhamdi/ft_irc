/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:01:54 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/01/18 21:06:49 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include "ACommand.hpp"

class User : public ACommand {
    public:
        User();
        void exec(std::string &user_infos,std::string &cmd_params, Client &client, Server &server) const;
        ~User();
    private:
};
