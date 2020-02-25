#include<vector>
#include<iostream>

using namespace std;

class HeapSort
{
public:
    void sort(vector<int> & arr)
    {
        for (int i = arr.size() / 2 - 1; i >= 0; --i)
        {
            max_heapify(arr, i, arr.size());
        }

        for (int i = arr.size() - 1; i > 0; --i)
        {
            int tmp = arr[0];
            arr[0] = arr[i];
            arr[i] = tmp;
            max_heapify(arr, 0, i);
        }
    }

    void build_max_heap(vector<int>& arr)
    {
        for (int i = arr.size() / 2 - 1; i >= 0; --i)
        {
            max_heapify(arr, i, arr.size());
        }
    }

    void build_min_heap(vector<int>& arr)
    {
        for (int i = arr.size() / 2 - 1; i >= 0; --i)
        {
            min_heapify(arr, i, arr.size());
        }
    }

    void min_heapify(vector<int>& arr, int i, int n)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        int smallest = i;

        if (l < n && arr[l] < arr[smallest])
        {
            smallest = l;
        }

        if (r < n && arr[r] < arr[smallest])
        {
            smallest = r;
        }

        if (smallest != i)
        {
            int tmp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = tmp;
            max_heapify(arr, smallest, n);
        }
    }

    void max_heapify(vector<int>& arr, int i, int n)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        int largest = i;

        if (l < n && arr[l] > arr[largest])
        {
            largest = l;
        }

        if (r < n && arr[r] > arr[largest])
        {
            largest = r;
        }

        if (largest != i)
        {
            int tmp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = tmp;
            max_heapify(arr, largest, n);
        }
    }
};

class PriorityQueue
{
private:
    vector<int> m_vector;
    HeapSort heap_sort;
    bool max_or_min;
public:
    PriorityQueue(bool max_or_min) : max_or_min(max_or_min)
    {
    }
    void push(int val)
    {
        m_vector.push_back(val);
        if (max_or_min)
        {
            heap_sort.build_max_heap(m_vector);
        }
        else
        {
            heap_sort.build_min_heap(m_vector);
        }
    }

    int size()
    {
        return m_vector.size();
    }

    void pop()
    {
        if (!m_vector.empty())
        {
            m_vector.erase(m_vector.begin());
        }

        if (!m_vector.empty())
        {
            if (max_or_min)
            {
                heap_sort.build_max_heap(m_vector);
            }
            else
            {
                heap_sort.build_min_heap(m_vector);
            }
        }
    }

    int top()
    {
        return m_vector[0];
    }
};

class MedianFinder {
private:
    PriorityQueue left = true;
    PriorityQueue right = false;

    void resize() {
        if (left.size() >= right.size() + 2) {
            right.push(left.top());
            left.pop();
        }
        else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }

public:
    /** initialize your data structure here. */
    MedianFinder() {
        left.push(INT_MIN);
        right.push(INT_MAX);
    }

    void addNum(int num) {
        int lmax = left.top(), rmin = right.top();
        if (num <= lmax)
        {
            left.push(num);
        }
        else
        {
            right.push(num);
        }
        resize();
    }

    double findMedian() {
        if (left.size() == right.size())
            return ((double)left.top() + right.top()) / 2;
        else
            return left.top();
    }
};


void test()
{
    MedianFinder m;
    m.addNum(1);
    m.addNum(2);
    m.addNum(3);
    m.addNum(4);
    m.addNum(5);

    cout << m.findMedian();
}