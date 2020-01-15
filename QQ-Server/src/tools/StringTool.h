#ifndef QQ_SERVER_STRINGTOOL_H
#define QQ_SERVER_STRINGTOOL_H

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class StringTool
{
public:
    static void split(const string &s, char delim, vector<string> &elems)
    {
        stringstream ss(s);
        string item;

        while (getline(ss, item, delim))
        {
            if (item.length() > 0)
            {
                elems.push_back(item);
            }
        }
    }
};

#endif