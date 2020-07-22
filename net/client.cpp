#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <threadPool.h>

int main() {
    
    //1. create sock
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == -1) {
        std::cerr << "socket error" << std::endl;
        return 0;
    }

    //2. connect server
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = 8005;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(client, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "connect server error" << std::endl;
        return 0;
    }

    //3. send message
    char buf[255];
    char data[255];
    while (true) {
        std::cin >> data;
        if (std::strcmp(data, "exit") == 0) {
            send(client, data, strlen(data), 0);
            break;
        }
        send(client, data, strlen(data), 0);
        memset(data, 0, sizeof(data));
        std::string returnMsg = "";
        int recvLen = 0;
        recvLen = recv(client, buf, sizeof(buf), 0);
        returnMsg += buf;

        memset(buf, 0, sizeof(buf));
        
        std::cout << returnMsg << std::endl;
    }
    close(client);
}