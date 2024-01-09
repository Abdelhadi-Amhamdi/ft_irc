#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <poll.h>
#include <sstream>
#include "Client.hpp"
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>

#define MAX_CLIENTS 10

struct sockaddr_in my_addr;

std::vector<Client> clients;
std::string pass;

void _error(std::string msg) {
	std::cerr << msg << std::endl;
}

void test(std::string &data, Client &c) {
	std::string key, pass, nick, login, name;
	std::stringstream s(data);
	s >> key;
	if (key == "PASS") {
		s >> pass;
		c.setPassword(pass);
	} else if (key == "NICK") {
		s >> nick;
		c.setNickname(nick);
	} else if (key == "USER") {
		s >> login;
		c.setLogin(login);
		s.seekg(5, std::ios::cur);
		s >> name;
		c.setRealName(name);
		c.setlogedin();
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3)
		return (_error("Error: inalid args, usage: (./ircserv <port> <password>)!"), 1);
	int port = std::stoi(argv[1]);
	pass = argv[2];

	int sock_fd = socket(AF_INET, SOCK_STREAM,0);
	if (sock_fd == -1)
		return (_error("Error: socket cannot be created!"), 1);

	
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(port);

	if (bind(sock_fd, reinterpret_cast<struct sockaddr*>(&my_addr), sizeof(my_addr)) == -1)
		return (close(sock_fd), _error("Error: cant bind the socket to the giver address and port"), 1);

	if (listen(sock_fd, 1) == -1)
		return (close(sock_fd), _error("Error"), 1);

	std::cout << "Server listening on port " << port << std::endl;

	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	struct pollfd fds[1000];
	fds[0].fd = sock_fd;
	fds[0].events = POLLIN;
	int fd_num = 1;
	while (true) {
		if (poll(fds, fd_num, 10000) > 0) {
			for (size_t i = 0; i < fd_num; i++) {
				if ((fds[i].revents & POLLIN) == POLLIN) {
					if (fds[i].fd == sock_fd) {
						int cfd = accept(sock_fd, reinterpret_cast<struct sockaddr*>(&client_addr), &len);
						if (cfd == -1)
							continue;
						std::cout << "Accepted connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
						fds[fd_num].fd = cfd;
						fds[fd_num].events = POLLIN;
						++fd_num;
						Client cl;
						clients.push_back(cl);
						break;
					} else {
						char buffer[500] = {0};
						ssize_t bytes = recv(fds[i].fd, buffer, sizeof(buffer), 0);
						if (!clients[i].islogedin()) {
							std::string buff = buffer;
							test(buff, clients[i]);
							if (clients[i].islogedin()) {
								std::string wc_msg = ":localhost 001 " + clients[i].getNickname() + " : Welcome to the IRC server, " + clients[0].getNickname() + "!\r\n";
								send(fds[i].fd, wc_msg.c_str(), wc_msg.size(), 0);
							}
						}
						else
							std::cout << buffer << std::endl;
					}
				}
			}
		}
	}
	return (0);
}
