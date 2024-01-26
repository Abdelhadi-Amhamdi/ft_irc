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

void ChannelMode::setInvitOnly(char sign)
{
    assert(sign == '+' || sign == '-');
    if (sign == '+')
        inviteOnly = true;
    else
        inviteOnly = false;
}

bool ChannelMode::getTopic() const { return hasTopic; }

void ChannelMode::setTopic(char sign)
{
    assert(sign == '+' || sign == '-');
    if (sign == '+')
        hasTopic = true;
    else
        hasTopic = false;
}

std::string ChannelMode::getKey() const { return key; }

void ChannelMode::setKey(char sing, const std::string &key_, int& indexKey)
{
    if (sing == '+')
    {    
        hasLimit = true;    
        key = key_;
        indexKey++;
    }
    else {
        hasKey = false;
        key = "";
    }
}

int ChannelMode::getLimit() const { return limit; }

void ChannelMode::setLimit(char sign, std::string key, int& indexKey)
{
    assert(sign == '+' || sign == '-');

    if (sign == '-')
        this->hasLimit = false;
    else
    {
        this->hasLimit = true;
        indexKey++;
        limit = std::stoi(key);
    }

    // if (limit_ > 0)
    // {
    //     hasLimit = true;
    //     limit = limit_;
    // }
    // else
    //     std::cout << __LINE__ << "response for invalid argurment\n";
}

bool ChannelMode::getHasLimit() const { return hasLimit; }
