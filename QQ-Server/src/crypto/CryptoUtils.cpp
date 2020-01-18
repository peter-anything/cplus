#include "CryptoUtils.h"

#include <sstream>
#include <assert.h>

string PBKDF2PasswordHasher::ALGORITHM  = "PBKDF2_SHA256";
int PBKDF2PasswordHasher::ITERATIONS = 150000;

void PBKDF2PasswordHasher::encode(string &password, string &salt_str, string &encoded_pwd)
{
    assert(password != "");
    assert(salt_str != "");
    PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf2;
    byte salt[12], key[32];
    /* Hard coded for testing purposes */
    memcpy(salt, salt_str.c_str(), 12);

    /* Rare segfault on this line */
    pbkdf2.DeriveKey(
        key, sizeof(key), 0, (byte*)password.data(),
        password.size(), salt, sizeof(salt), ITERATIONS
    );

    ostringstream oss;
    oss << ALGORITHM << "$" << ITERATIONS << "$" << salt_str << "$";
    StringSource(key, sizeof(key), true, new HexEncoder(new FileSink(oss)));

    encoded_pwd = oss.str();
}

string PBKDF2PasswordHasher::generate_random_string()
{
    int length = 12;
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);
    srand((unsigned)time(NULL));
    for (int i = 0; i < length; i++)
    {
        result[i] = charset[rand() % charset.length()];
    }

    return result;
}

void PBKDF2PasswordHasher::make_password(string& password, string& encoded_pwd)
{
    string salt = generate_random_string();
    encode(password, salt, encoded_pwd);
}

bool PBKDF2PasswordHasher::verify(string& password, string& encoded_pwd)
{
    vector<string> v;
    StringTool::split(encoded_pwd, '$', v);

    if (v.size() < 1)
    {
        return false;
    }

    string tmp_encode_pwd;
    string salt = v[2];

    encode(password, salt, tmp_encode_pwd);

    return encoded_pwd == tmp_encode_pwd;
}