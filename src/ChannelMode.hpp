#ifndef ChannelMode_HPP
#define ChannelMode_HPP


#include <iostream>
#include <string>

class ChannelMode {
	private:
        bool    inviteOnly;
        bool    topic;
        bool    hasLimit;
        int     limit;
        bool    hasKey;
        std::string key;

    public:
        ChannelMode();
        
        ChannelMode(const std::string& key);

        bool getInvitOnly() const;
        void setInvitOnly(char sign);

        bool getTopic() const;
        void setTopic(char sign);

        std::string getKey() const;
        void setKey(const std::string &key_);

        int getLimit() const;
        void setLimit(char sign, std::string key);

};

#endif // ChannelMode_HPP
