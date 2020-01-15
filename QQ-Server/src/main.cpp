#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <cerrno>
#include <cstring>

#include "MessageController.h"

#define MAX_MSG_SIZE 256
#define SERVER_PORT 9987
#define BACKLOG 512

#include <vector>

int main()
{
    int sock_fd, client_fd; /*sock_fd：监听socket；client_fd：数据传输socket */
    struct sockaddr_in ser_addr{}; /* 本机地址信息 */
    struct sockaddr_in cli_addr{}; /* 客户端地址信息 */
    char msg[MAX_MSG_SIZE];/* 缓冲区*/
    int ser_sockfd = socket(AF_INET, SOCK_STREAM, 0);/*创建连接的SOCKET */
    if (ser_sockfd < 0) {/*创建失败 */
        fprintf(stderr, "socker Error:%s\n", strerror(errno));
        exit(1);
    }
    /* 初始化服务器地址*/
    socklen_t addrlen = sizeof(struct sockaddr_in);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(SERVER_PORT);

    int opt = 1;
    setsockopt(ser_sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &opt, sizeof(ser_addr));

    if (bind(ser_sockfd, (struct sockaddr *) &ser_addr, sizeof(struct sockaddr_in)) < 0) { /*绑定失败 */
        fprintf(stderr, "Bind Error:%s\n", strerror(errno));
        exit(1);
    }
    /*侦听客户端请求*/
    if (listen(ser_sockfd, BACKLOG) < 0) {
        fprintf(stderr, "Listen Error:%s\n", strerror(errno));
        close(ser_sockfd);
        exit(1);
    }

    printf("listening on 9987\n");

    while (true) {/* 等待接收客户连接请求*/
        int cli_sockfd = accept(ser_sockfd, (struct sockaddr *) &cli_addr, &addrlen);
        if (cli_sockfd <= 0) {
            fprintf(stderr, "Accept Error:%s\n", strerror(errno));
        } else {/*开始服务*/
            printf("received a connection from %s\n", inet_ntoa(cli_addr.sin_addr));

            MessageController::handleMessage(cli_sockfd, msg, MAX_MSG_SIZE);
        }
    }
}