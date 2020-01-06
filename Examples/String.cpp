#include "String.h"

//String();
//String(int n, char c);
//String(const char* source);
//String(const String& s);
//String& operator = (char* s);
//String& operator = (const String& s);
//~String();
//char& operator[] (int i);
//const char& operator[] (int i) const;
//String& operator += (const String& s);
//String& operator += (const char* s);
//friend ostream& operator << (ostream& out, String& s);
//friend iostream& operator >> (iostream& in, String& s);
//friend bool operator < (const String& left, const String& right);
//friend bool operator > (const String& left, const String& right);
//friend bool operator == (const String& left, const String& right);
//char* getData();

String::String()
{
    data = new char[1];
    data[0] = '\0';
    size = 0;
}

String::String(int n, char c)
{
    data = new char[n + 1];
    size = n;
    for (int i = 0; i < n; i++)
    {
        data[i] = c;
    }
    data[n] = '\0';
}

String::String(const char* source)
{
    if (source == NULL)
    {
        data = new char[1];
        data[0] = '\0';
        size = 0;
    }
    else
    {
        size = strlen(source);
        data = new char[size + 1];
        strcpy_s(data, size + 1, source);
    }
}

String::String(const String& s)
{
    data = new char[s.size + 1];
    strcpy_s(data, s.size + 1, s.data);
    size = s.size;
}

String& String::operator = (char* s)
{
    if (data != NULL)
    {
        delete[] data;
    }
    size = strlen(s);
    data = new char[size + 1];
    strcpy_s(data, size + 1, s);

    return *this;
}

String& String::operator = (const String & s)
{
    if (this == &s)
    {
        return *this;
    }

    if (data != NULL)
    {
        delete[] data;
    }

    size = strlen(s.data);
    data = new char[size + 1];
    strcpy_s(data, size + 1, s.data);

    return *this;
}

String::~String()
{
    if (data != NULL)
    {
        delete []data;
        data = NULL;
        size = 0;
    }
}

char& String::operator[] (int i)
{
    return data[i];
}

const char& String::operator[] (int i) const
{
    return data[i];
}

String String::operator+= (const String& s) 
{
    int len = size + s.size + 1;
    char* temp = data;
    data = new char[len];
    size = len - 1;
    strcpy_s(data, strlen(temp) + 1, temp);
    strcat_s(data, len, s.data);

    delete []temp;

    return *this;
}

String String::operator+= (const char* s)
{
    if (s == NULL)
    {
        return *this;
    }
    int len = size + strlen(s) + 1;
    char* temp = data;
    data = new char[len];
    size = len - 1;
    strcpy_s(data, strlen(temp) + 1, temp);
    strcat_s(data, len, s);

    delete[]temp;

    return *this;
}

ostream& operator << (ostream& out, String& s)
{
    for (int i = 0; i < s.size; i++)
    {
        out << s[i];
    }

    return out;
}

iostream& operator >> (iostream& in, String& s)
{
    char p[50];
    in.getline(p, 50);
    s = p;

    return in;
}

bool operator < (const String& left, const String& right)
{
    int i = 0;
    while (left[i] == right[i] && left[i] != 0 && right[i] != 0)
    {
        i++;
    }

    return left[i] - right[i] < 0 ? true : false;
}

bool operator > (const String& left, const String& right)
{
    int i = 0;
    while (left[i] == right[i] && left[i] != 0 && right[i] != 0)
    {
        i++;
    }

    return left[i] - right[i] > 0 ? true : false;
}

bool operator == (const String& left, const String& right)
{
    int i = 0;
    while (left[i] == right[i] && left[i] != 0 && right[i] != 0)
    {
        i++;
    }

    return left[i] - right[i] == 0 ? true : false;
}

bool operator != (const String& left, const String& right)
{
    int i = 0;
    while (left[i] == right[i] && left[i] != 0 && right[i] != 0)
    {
        i++;
    }

    return left[i] - right[i] != 0 ? true : false;
}

char* String::getData(){
    return data;
}

int main()
{
    String source = "Hello, world";
    String source2 = "Hello, world2";
    String source3 = "Hello, world3";
    (source2 = source3) = source;
    cout << source << endl;
    cout << source2 << endl;
    cout << source3 << endl;
}