#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

struct Value
{
    int value;
    list<int>::iterator iter;
    Value(int v, list<int>::iterator iter) : value(v), iter(iter) {}
};

class LRUCache {
private:
    int m_capacity;
    list<int> m_list;
    unordered_map<int, Value> hash;

public:
    LRUCache(int capacity) {
        this->m_capacity = capacity;
    }

    int get(int key) {
        unordered_map<int, Value>::iterator iter = hash.find(key);
        if (iter != hash.end())
        {
            m_list.splice(m_list.begin(), m_list, iter->second.iter);

            return iter->second.value;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value) {
        unordered_map<int, Value>::iterator iter = hash.find(key);
        if (iter != hash.end())
        {
            m_list.splice(m_list.begin(), m_list, iter->second.iter);
            iter->second.value = value;
        }
        else
        {
            if (hash.size() == m_capacity)
            {
                hash.erase(m_list.back());
                m_list.pop_back();
            }
            m_list.push_front(key);
            Value v(value, m_list.begin());
            hash.insert(pair<int, Value>(key, v));
        }
    }
};

void test()
{
    LRUCache lru_cache(2);
    lru_cache.put(1, 1);
    lru_cache.put(2, 2);
    cout << lru_cache.get(1);
}