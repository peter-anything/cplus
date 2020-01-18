//
// Created by peter on 2020/1/10.
//

#ifndef QQ_SERVER_MESSAGECONTROLLER_H
#define QQ_SERVER_MESSAGECONTROLLER_H

#include <string.h>
#include <iostream>
#include <map>

using namespace std;

class MessageType
{
public:
    static string LOGIN;
    static string LOGOUT;
};

class MessageController
{
public:
    static void handleMessage(int cli_sockfd, char *msg, unsigned long max_size);
private:
    static map<string, int> client_socket_map;
};

#endif //QQ_SERVER_MESSAGECONTROLLER_H
