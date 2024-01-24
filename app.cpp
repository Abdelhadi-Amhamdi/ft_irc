
// // #include <iostream>
// // #include <sys/socket.h>
// // #include <arpa/inet.h>
// // #include <netdb.h>



// // int main() {

// //     int sock = socket(AF_INET, SOCK_STREAM, 0);
// //     if (sock == -1) 
// //         return (0);
// //     struct sockaddr cl;
// //     struct hostent* host_info = gethostbyname("api.publicapis.org");
// //     socklen_t s = sizeof(cl);
// //     if (connect(sock, &cl, &s) == -1)
// //         return (0);
// //     const std::string a = "/GET /entries HTTP/1.1\r\n";
// //     const std::string b = "Host: api.publicapis.org\r\n";
// //     send(sock, a.c_str(), a.size(), 0);
// //     send(sock, b.c_str(), b.size(), 0);
// //     char buffer[500] = {0};
// //     recv(sock, buffer, sizeof(buffer), 0);
// //     std::cout << buffer;
    
// // }

// #include <iostream>
// #include <cstring>
//  #include <netdb.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// int main() {
//     // http://universities.hipolabs.com/
//     const char* hostname = "universities.hipolabs.com";
//     struct hostent* host_info = gethostbyname(hostname);

//     if (host_info != NULL) {
//         printf("Official name: %s\n", host_info->h_name);
//         for (int i = 0; host_info->h_aliases[i] != NULL; ++i)
//             printf("Alias: %s\n", host_info->h_aliases[i]);
//         printf("Address type: %s\n",
//                (host_info->h_addrtype == AF_INET) ? "IPv4" : "Unknown");
//         for (int i = 0; host_info->h_addr_list[i] != NULL; ++i) {
//             printf("IP address: %s\n",
//                    inet_ntoa(*(struct in_addr*)host_info->h_addr_list[i]));
//         }
//     } else {
//         herror("gethostbyname");
//     }

//     // return 0;
//     // const char* serverHostname = "api.publicapis.org";
//     const char* request = "GET / HTTP/1.1\r\nHost: universities.hipolabs.com\r\n\r\n";
//     std::cout << request;
//     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockfd == -1) {
//         perror("Socket creation failed");
//         return 1;
//     }

//     struct sockaddr_in serverAddress;
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_port = htons(80);
//     inet_pton(AF_INET, "18.208.153.178", &(serverAddress.sin_addr));

//     if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
//         perror("Connection failed");
//         close(sockfd);
//         return 1;
//     }
//     if (send(sockfd, request, strlen(request), 0) == -1) {
//         perror("Send failed");
//         close(sockfd);
//         return 1;
//     }   
//     char buffer[500] = {0};
//     recv(sockfd, buffer, 500, 0);
//     std::cout << buffer;
//     close(sockfd);

//     return 0;
// }

#include <iostream>
#include <curl/curl.h>


int main() {
    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://catfact.ninja/fact");
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cout << "Error\n";
        }
        std::cout << res;
        curl_easy_cleanup(curl);
    }
}