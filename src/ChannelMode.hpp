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
        void setInvitOnly(char sign);

        bool getTopic() const;
        void setTopic(char sign);

        std::string getKey() const;
        void setKey(char sing, const std::string &key_, int& inexKey);

        int getLimit() const;
        void setLimit(char sign, std::string key, int& indexKey);

        bool getHasLimit() const;

};

#endif // ChannelMode_HPP
