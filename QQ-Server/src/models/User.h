#ifndef QQ_SERVER_USER_H
#define QQ_SERVER_USER_H

#include <iostream>

using namespace std;

class User
{
public:
    int id;
    int qq_id;
    string nickname;
    string mobile;
    string password;
    string email;
    string avatar;
    string address;
    short sex;
    short age;
    string created_at;
    string updated_at;
public:
    string& get_pwd_by_username(string &pwd, string &name);
};

#endif
