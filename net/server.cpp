#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

std::string getCurrentTimeStr()
{
    time_t t = time(nullptr);
    char ch[64] = {0};
    strftime(ch, sizeof(ch) - 1, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return ch;
}

void processClientRequest(int connfd)
{
    char buf[255];
    int recvLen = 0;
    memset(buf, 0, sizeof(buf));
    std::string returnMsg = "";
    while (true)
    {
        recvLen = recv(connfd, buf, sizeof(buf), 0);
        returnMsg += buf;
        if (returnMsg == "exit")
        {
            std::cout << "recv client exit" << std::endl;
            break;
        }
        returnMsg = "Hello, " + returnMsg + "-----" + getCurrentTimeStr();
        std::strcpy(buf, returnMsg.c_str());
        send(connfd, buf, sizeof(buf), 0);
        memset(buf, 0, sizeof(buf));
        returnMsg = "";
    }
    close(connfd);
}

int main()
{

    //1. create socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        std::cerr << "socket error" << std::endl;
        return 0;
    }

    //2. bind address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 8005;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenfd, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "bind address error" << std::endl;
        return 0;
    }

    //3. listen
    if (listen(listenfd, 5) == -1)
    {
        std::cerr << "listen address error" << std::endl;
        return 0;
    }

    std::cout << "server listening..." << std::endl;

    //4. accept
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    while (true)
    {
        int connfd = accept(listenfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
        std::cout << "accept client!" << std::endl;
        std::thread t(processClientRequest, connfd);
        t.detach();
    }
    close(listenfd);
}