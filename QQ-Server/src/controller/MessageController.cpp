//
// Created by peter on 2020/1/10.
//

#include "MessageController.h"
#include "rapidjson/document.h"
#include <sys/socket.h>
#include <string.h>

#include <iostream>

using namespace std;
using namespace rapidjson;

string MessageType::LOGIN = "login";
string MessageType::LOGOUT = "logout";

void MessageController::handleMessage(int cli_sockfd, char *msg, size_t max_size)
{
    recv(cli_sockfd, msg, max_size, 0); /* 接受数据*/

    // Don't know why, \003 is in the last of string from python ujson.
    string recv_msg = msg;
    recv_msg.replace(recv_msg.find('\003'), 1, "");

    Document document;
    document.Parse(recv_msg.data());

    string type = document["type"].GetString();

    if (type == MessageType::LOGIN)
    {
        Value &payloadObj = document["payload"];
        string username = payloadObj["username"].GetString();
        string password = payloadObj["password"].GetString();

        cout << username << '\t' << password;
    }

    const char * send_msg = "hi, I am server!";
    strcpy(msg, send_msg);
    cout << send_msg << endl;
    send(cli_sockfd, msg, strlen(send_msg), 0); /*发送的数据*/
}