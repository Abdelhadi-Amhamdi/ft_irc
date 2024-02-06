/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:55:37 by aamhamdi          #+#    #+#             */
/*   Updated: 2024/02/06 21:55:41 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelMode.hpp"
#include <cassert>
#include <string>

ChannelMode::ChannelMode() :  inviteOnly(false), hasTopic(false), hasLimit(false), hasKey(false)
{}

ChannelMode::ChannelMode(const std::string& key)
    : inviteOnly(false), hasTopic(false), hasLimit(false)
{
    if (key.empty())
        hasKey = false;
    else
        hasKey = true;
    this->key = key;
}

bool ChannelMode::getInvitOnly() const { return inviteOnly; }

void ChannelMode::setInvitOnly(bool value)
{
    this->inviteOnly = value;
}

bool ChannelMode::getTopic() const { return hasTopic; }

void ChannelMode::setTopic(bool value)
{
    this->hasTopic = value;
}

std::string ChannelMode::getKey() const { return key; }

void ChannelMode::setKey(bool hasKey, const std::string &key_)
{
    this->hasKey = hasKey;
    this->key = key_;
}

int ChannelMode::getLimit() const { return limit; }

void ChannelMode::setLimit(bool hasLimit, size_t limit) {
    this->hasLimit = hasLimit;
    this->limit = limit;
}

bool ChannelMode::getHasLimit() const { return hasLimit; }


bool ChannelMode::getHasKey() const {
    return hasKey;
}