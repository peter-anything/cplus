#include <iostream>
#include <thread>
#include <list>

using namespace std;

class Test
{
public:
    void test_insert() {
        for (int i = 0; i < 1000000; i++)
        {
            cout << "insert to v i: " << i << endl;
            l.push_back(i);
        }
    };

    void test_delete() {
        for (int i = 0; i < 1000000; i++)
        {
            if (!l.empty())
            {
                int i = l.front();
                l.pop_front();
                cout << "delete from v i: " << i << endl;
            }
            else
            {
                cout << "empty v" << endl;
            }
        }
    }
private:
    list<int> l;
};

int main() {
    Test t;
    thread th1(&Test::test_insert, ref(t));
    thread th3(&Test::test_delete, ref(t));
    th3.join();
    th1.join();

}
