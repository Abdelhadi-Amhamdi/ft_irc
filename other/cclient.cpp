#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 3) {
		return (1);
	}
	string cmd = argv[1];
	string port_str = argv[2];
	size_t port = stoi(port_str);
	struct sockaddr_in my_addr;
	int sock_fd = socket(AF_INET, SOCK_STREAM,0);
	if (sock_fd == -1){
		cout << "Error : socket cant be created\n";
		return (1);
	}

	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	my_addr.sin_family = AF_INET;
	socklen_t len = sizeof(my_addr);
	int s = connect(sock_fd, reinterpret_cast<struct sockaddr*>(&my_addr), len);
	if (s == -1) {
		cout << "Error\n";
		return (1);
	}
	sleep(1);
	// char buf[500] = {0};
	// recv(sock_fd, buf, sizeof(buf), 0);
	// std::cout << buf << std::endl;
	send(sock_fd, cmd.c_str(), cmd.size(),0);
	// while (true) {
	// 	std::string msg;
	// 	std::cout << "please Entre a message\n";
	// 	std::getline(std::cin, msg);
	// 	send(sock_fd, msg.c_str(), msg.size(),0);
	// }
	close(sock_fd);
	return (0);
}
