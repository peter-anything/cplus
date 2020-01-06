#ifndef STRING_H
#define STRING_H

#include <iostream>

using namespace std;

class String
{
public:
    String();
    String(int n, char c);
    String(const char* source);
    String(const String& s);
    String& operator = (char* s);
    String& operator = (const String& s);
    ~String();
    char& operator[] (int i);
    const char& operator[] (int i) const;
    String operator += (const String& s);
    String operator += (const char* s);
    friend ostream& operator << (ostream& out, String& s);
    friend iostream& operator >> (iostream& in, String& s);
    friend bool operator < (const String& left, const String& right);
    friend bool operator > (const String& left, const String& right);
    friend bool operator == (const String& left, const String& right);
    friend bool operator != (const String& left, const String& right);
    char* getData();
private:
    int size;
    char* data;
};

#endif // !STRING_H

