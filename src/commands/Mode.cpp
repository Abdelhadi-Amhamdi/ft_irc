/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:07:59 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/15 00:36:41 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"
#include "../Replies.hpp"
#include "ACommand.hpp"
#include <exception>
#include <sstream>
#include <string>

Mode::Mode(Server& server)
    : ACommand("MODE"), server(server)
{
    signs['+'] = true;
    signs['-'] = false;
}
Mode::~Mode()
{
    
}

bool    isSign(char c)
{
    return (c == '-' || c == '+');
}

const std::string   Mode::getArgs()
{
    std::string args;

    for (size_t i = 2; i < params.size(); i++)
    {
        args += " ";
        args += params[i];
    }
    return args;
}

void    Mode::formate(const std::string& buffer, Connection& user)
{
    std::stringstream ss(buffer);

    std::string current;

    if (buffer[0] == ':')// get prefix.
        ss >> current;
    ss >> current; // get command name.

    if (ss >> channelName)
    {
        if (channelName[0] != '#')
            throw std::logic_error(ERR_NOSUCHCHANNEL(user.getNickname() ,channelName));
        channelName.erase(0, 1);
        channel = server.getChannelManager().getChannelByName(channelName);
        if (channel == NULL)
            throw std::logic_error(ERR_NOSUCHCHANNEL(user.getNickname() ,channelName));
    }
    if (!(ss >> modeString))    
        throw std::logic_error(ERR_NEEDMOREPARAMS(user.getNickname(), "MODE"));
    while (ss >> current) {
        args.push_back(current);
    }
}

void    Mode::clear()
{
    this->args.clear();
    this->modes.clear();
    this->valideArgs.clear();
    this->channelName.clear();
    this->modeString.clear();
    this->channel = NULL;
}


void    Mode::setIMode(char sign, ChannelMode& mode, std::string::iterator& it)
{
    bool execute = (signs[sign] != mode.getInvitOnly()) ? true : false;
    if (execute == true)
    {
        mode.setInvitOnly(signs[sign]);
        pushToModes(sign, *it);
    }
}
void    Mode::setTMode(char sign, ChannelMode& mode, std::string::iterator& it)
{
    bool execute = (signs[sign] != mode.getTopic()) ? true : false;
    if (execute == true)
    {
        mode.setTopic(signs[sign]);
        pushToModes(sign, *it);
    }
}

void    Mode::pushToModes(char sign, char flag)
{
    std::pair<char, char> pair;
    pair.first = sign;
    pair.second = flag;
    this->modes.push_back(pair);
}

void    Mode::setLMode(char sign, ChannelMode& mode, std::string::iterator& it)
{
    if (signs[sign] == false)
    {
        if (mode.getHasLimit() == true)
        {
            mode.setLimit(false, 0);
            pushToModes(sign, *it);
        }
    }
    else if (!args.empty())
    {
        std::string arg = args.front();
        args.pop_front();
        int limit = std::atoi(arg.c_str());
        if (limit > 0)
        {
            valideArgs += " " + arg;
            mode.setLimit(true, limit);
            pushToModes(sign, *it);
        }
    }
}
void    Mode::setKMode(char sign, ChannelMode& mode, std::string::iterator& it)
{
    if (signs[sign] == false)
    {
        if (mode.getHasKey() == true)
        {
            mode.setKey(false, "");
            pushToModes(sign, *it);
        }
    }
    else if (!args.empty())
    {
        std::string arg = args.front();
        args.pop_front();
        valideArgs += " " + arg;
        mode.setKey(true, arg);
        pushToModes(sign, *it);
    }
}

void Mode::setOMode(char sign, std::string::iterator& flag, Connection& user)
{
    try {
        if (args.empty())
            return ;
        std::string target = args.front();
        args.pop_front();
        Client* client = server.getClientManager().getClientByNickname(target);
        if (client == NULL)
            throw std::logic_error(ERR_NOSUCHNICK(user.getNickname(), target));
        if (channel->isMemberInChannel(user.getFd()) == false)
            throw std::logic_error(ERR_USERNOTONCHANNEL(user.getNickname(), target, channelName));
        if (sign == '+')
        {
            if (channel->isMemberInChannel(client->getFd()) == false)
                return;
            channel->addAdmin(client->getFd());
        }
        else
            channel->delAdmin(client->getFd());
        valideArgs += " " + target;
        pushToModes(sign, *flag);
    } catch (std::exception& e) {
        sendResponse(e.what(), user.getFd());
    }
}

void    Mode::exec(char& sign, std::string::iterator& flag, ChannelMode& mode, Connection& user)
{
    switch (*flag) {
        case 'i':
            setIMode(sign, mode, flag);
            break;
        case 'l':
            setLMode(sign, mode, flag);
            break;
        case 'k':
            setKMode(sign, mode, flag);
            break;
        case 't':
            setTMode(sign, mode, flag);
            break;
        case 'o':
            setOMode(sign, flag, user);
            break;
        default:
            sendResponse(ERR_UNKNOWNMODE(user.getNickname(), *flag), user.getFd());
    }
}

void    Mode::setModes(Connection& user)
{
    ChannelMode& mode = channel->getMode();
    if (!isSign(modeString[0]))
        modeString.insert(modeString.begin(), '+');
    char sign = modeString[0];

    for(std::string::iterator it = modeString.begin(); it != modeString.end(); ++it)
    {
        while (isSign(*it) && it != modeString.end())
        {
            sign = *it;
            it++;
        }
        if (it  != modeString.end())
            exec(sign, it, mode, user);
    }
}

void Mode::Execute(std::string &buffer, Connection &user, Server &server)
{
    (void) server;
    clear();
    try {
            
        formate(buffer, user);
        if (channel->checkIfAdmin(user.getFd()) == false)
        {
            sendResponse(ERR_NOTCHANOPER(user.getNickname(), channelName), user.getFd());
            return;
        }
        setModes(user);
        modeString.clear();
        if (modes.empty())
            return;
        char sign = modes[0].first;
        modeString += sign;
        for (size_t i = 0; i < modes.size(); i++)
        {
            char first = modes[i].first;
            if (sign != first)
            {
                modeString += first;
                sign = first;
            }
            modeString += modes[i].second;
        }
        channel->broadCastResponse(RPL_MODE(user.getNickname(), channelName, modeString, valideArgs));
    } catch (std::exception& e) {
        sendResponse( e.what(), user.getFd());
    }
}


