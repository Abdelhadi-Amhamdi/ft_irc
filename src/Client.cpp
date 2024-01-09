

#include "Client.hpp"

// Client::Client(int fd, std::string nickname, std::string password, std::string login, std::string real_name) 
//     : fd(fd), nickname(nickname), password(password), login(login), real_name(real_name), logedin(false) {}

int Client::getFd() const {return (fd);}
const std::string & Client::getNickname() const {return (nickname);}
const std::string & Client::getPassword() const {return (password);}
const std::string & Client::getLogin() const {return (login);}
const std::string & Client::getRealName() const {return (real_name);} 
bool Client::islogedin() const {return this->logedin;}


void Client::setFd(int arg) {this->fd = arg;}
void Client::setNickname(const std::string &arg) {this->nickname = arg;}
void Client::setPassword(const std::string &arg) {this->password = arg;}
void Client::setLogin(const std::string &arg) {this->login = arg;}
void Client::setRealName(const std::string &arg) {this->real_name = arg;}
void Client::setlogedin() {this->logedin = true;}
