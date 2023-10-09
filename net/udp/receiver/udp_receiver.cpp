#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    // 解析命令行参数中的端口号
    int port = std::atoi(argv[1]);

    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error: Could not create socket" << std::endl;
        return 1;
    }

    // 设置服务器地址结构
    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字到指定端口
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Could not bind to port " << port << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "UDP server is listening on port " << port << std::endl;

    while (true) {
        char buffer[1024]; // 用于存储接收的数据
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        // 接收数据包
        ssize_t recvLen = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                   (struct sockaddr *)&clientAddr, &clientAddrLen);

        if (recvLen == -1) {
            std::cerr << "Error: Could not receive data" << std::endl;
            break;
        }

        std::cout << "Received a packet of length " << recvLen << " bytes" << std::endl;
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}

