//
// Created by peter on 2020/1/10.
//


#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <sys/socket.h>
#include <string.h>

#include "MessageController.h"
#include "User.h"
#include "CryptoUtils.h"

#include <iostream>
#include <map>

using namespace std;
using namespace rapidjson;

string MessageType::LOGIN = "login";
string MessageType::LOGOUT = "logout";
map<string, int> MessageController::client_socket_map;

void MessageController::handleMessage(int cli_sockfd, char *msg, size_t max_size)
{

    recv(cli_sockfd, msg, max_size, 0); /* 接受数据*/

    // Don't know why, \003 is in the last of string from python ujson.
    string recv_msg = msg;
    try
    {
        recv_msg.replace(recv_msg.find('\003'), 1, "");
        recv_msg.replace(recv_msg.find('\177'), 1, "");
    }
    catch (exception &ex)
    {
        std::cout << ex.what() << endl;
    }
    Document document;
    document.Parse(recv_msg.data());

    string type = document["type"].GetString();

    if (type == MessageType::LOGIN)
    {
        std::cout << "login prcess" << endl;
        Value& payloadObj = document["payload"];
        string username = payloadObj["username"].GetString();
        string password = payloadObj["password"].GetString();

        User u;
        string encoded_pwd;

        encoded_pwd = u.get_pwd_by_username(encoded_pwd, username);

        Document jsonDoc;
        Document::AllocatorType& allocator_type = jsonDoc.GetAllocator();
        jsonDoc.SetObject();

        if(PBKDF2PasswordHasher::verify(password, encoded_pwd))
        {
            //MessageController::client_socket_map.insert(pair<string, int>(username, cli_sockfd));
            std::cout << "success" << endl;

            jsonDoc.AddMember("status", 1000, allocator_type);
            jsonDoc.AddMember("message", "login success", allocator_type);

        }
        else
        {
            jsonDoc.AddMember("status", 2000, allocator_type);
            jsonDoc.AddMember("message", "login failed", allocator_type);
        }

        StringBuffer string_buffer;
        Writer<StringBuffer> writer(string_buffer);
        jsonDoc.Accept(writer);

        string str_json = string_buffer.GetString();

        const char* send_msg = str_json.c_str();
        std::strcpy(msg, send_msg);
        std::cout << send_msg << endl;
        send(cli_sockfd, msg, strlen(send_msg), 0); /*发送的数据*/
    }
}