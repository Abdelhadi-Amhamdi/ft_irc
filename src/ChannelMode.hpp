#ifndef ChannelMode_HPP
#define ChannelMode_HPP


#include <iostream>
#include <string>

class ChannelMode {
	private:
        bool    inviteOnly;
        bool    hasTopic;
        bool    hasLimit;
        int     limit;
        bool    hasKey;
        std::string key;

    public:
        ChannelMode();
        ChannelMode(const std::string& key);
        bool getInvitOnly() const;
        void setInvitOnly(bool value);
        bool getTopic() const;
        void setTopic(bool value);
        std::string getKey() const;
        void setKey(bool hasKey, const std::string &key_);
        int getLimit() const;
        void setLimit(bool hasLimit, size_t limit); 
        bool getHasLimit() const;
        bool getHasKey() const; 

};

#endif // ChannelMode_HPP
