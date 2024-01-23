#include "ChannelMode.hpp"
#include <cassert>
#include <string>

ChannelMode::ChannelMode() :  inviteOnly(false), topic(false), hasLimit(false), hasKey(false)
{}

ChannelMode::ChannelMode(const std::string& key)
    : inviteOnly(false), topic(false), hasLimit(false)
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

bool ChannelMode::getTopic() const { return topic; }

void ChannelMode::setTopic(char sign)
{
    assert(sign == '+' || sign == '-');
    if (sign == '+')
        topic = true;
    else
        topic = false;
}

std::string ChannelMode::getKey() const { return key; }

void ChannelMode::setKey(const std::string &key_)
{
    hasLimit = true;
    key = key_;
}

int ChannelMode::getLimit() const { return limit; }

void ChannelMode::setLimit(char sign, std::string key)
{
    assert(sign == '+' || sign == '-');

    if (sign == '-')
        this->hasLimit = false;
    else
    {
        this->hasLimit = true;
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
