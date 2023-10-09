#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <IP> <port> <message>" << std::endl;
        return 1;
    }

    const char *ip = argv[1];
    int port = std::atoi(argv[2]);
    const char *message = argv[3];

    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error: Could not create socket" << std::endl;
        return 1;
    }

    // 设置目标服务器地址结构
    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "Error: Invalid IP address" << std::endl;
        close(sockfd);
        return 1;
    }

    // 发送消息
    ssize_t sendLen = sendto(sockfd, message, std::strlen(message), 0,
                             (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
    if (sendLen == -1) {
        std::cerr << "Error: Could not send data" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Sent " << sendLen << " bytes to " << ip << ":" << port << std::endl;

    // 关闭套接字
    close(sockfd);

    return 0;
}

