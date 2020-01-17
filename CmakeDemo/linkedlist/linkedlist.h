//
// Created by peter on 1/17/20.
//

#ifndef CMAKEDEMO_LINKEDLIST_H
#define CMAKEDEMO_LINKEDLIST_H

#include <iostream>

template <class T>
class LinkedList
{
private:
    struct Node
    {
        Node * next;
        T data;
    };
public:
    LinkedList()
    {
        head = new Node;
        head->next = nullptr;
    }

    void Add(T & data)
    {
        Node * new_data = new Node;
        new_data->next = nullptr;
        new_data->data = data;

        Node *q = head;
        while (q != nullptr && q->next != nullptr)
        {
            q = q->next;
        }

        q->next = new_data;
    }

    void Traverse()
    {
        Node * q =head;
        while( q != nullptr && q->next != nullptr )
        {
            std::cout << q->next->data << '\t';
            q = q->next;
        }

        std::cout << std::endl;
    }

    void EvenOddSort() {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return;
        }

        Node *evenHead = head->next;
        Node *oddHead = evenHead->next;
        Node *oddCopyHead = oddHead;
        Node *evenTail = evenHead;

        while (evenHead != nullptr && oddHead != nullptr) {
            evenTail = evenHead;
            evenHead->next = oddHead->next;
            evenHead = evenHead->next;
            if (evenHead != nullptr)
            {
                evenTail = evenHead;
                oddHead->next = evenHead->next;
                oddHead = oddHead->next;
            }

        }

        evenTail->next = oddCopyHead;
    }
private:
    Node * head = nullptr;
};

#endif //CMAKEDEMO_LINKEDLIST_H
