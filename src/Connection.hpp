#ifndef Connection_HPP
#define Connection_HPP
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <type_traits>

class Server;

class Connection {
    private:
        int         fd;
        std::string nickname;
        bool        isConnected;
        std::string buffer;
    public:
        Connection();
        Connection(int serverSocket);
        ~Connection();

        bool    getIsConnected() const { return isConnected; }
        void    setIsConnected(bool isConnected_) { isConnected = isConnected_; }

        const std::string getNickname() const { return nickname; }
        void    setNickname(const std::string &nickname_) { nickname = nickname_; }

        int     getFd() const { return fd; }

        void    receiveData();
        void    handleDAta(Server& server);

        // void    pass(Server& sever);

        void    connecte(Server& sever, std::string& pass);

        const std::string& getBuffer() const { return buffer; }


};

#endif // Connection_HPP
