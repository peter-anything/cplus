#include <set>
#include <iostream>

using namespace std;

class Number
{
public:
    int num = 0;
    set<int> related_nums;
public:
    Number(int n) : num(n)
    {
        cout << "constructor" << endl;
        related_nums.insert(n);
    };

    Number(const Number& other)
    {
        cout << "copy constructor" << endl;
        this->num = other.num;
        this->related_nums = other.related_nums;
    }
};

#include <vector>
#include <set>

int main() {

    int n = 7;
    vector<Number*> v_number;
    for (int i = 0; i < 7; i++)
    {
        Number* num = new Number(i);
        v_number.push_back(num);
    }

    Number* num0 = v_number[0];

    set<int> s = num0->related_nums;

    set<int>::iterator itr = num0->related_nums.begin();
    while (itr != num0->related_nums.end())
    {
        cout << "hello";
        cout << *itr << '\t';
        ++itr;
    }

    cout << "test";

    cout << endl;
}