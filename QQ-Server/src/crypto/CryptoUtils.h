#ifndef QQ_SERVER_CRYPTOUTILS_H
#define QQ_SERVER_CRYPTOUTILS_H

#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include <vector>
#include <iostream>

#include "StringTool.h"


using namespace CryptoPP;

using namespace std;

class PBKDF2PasswordHasher
{
private:
    static string ALGORITHM;
    static int ITERATIONS;
private:
    static string generate_random_string();
    static void encode(string& password, string & salt, string& encoded_pwd);
public:
    static void make_password(string& password, string& encoded_pwd);

    static bool verify(string& password, string& encoded_pwd);
};

#endif