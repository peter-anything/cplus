#include<iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        
        ListNode* extra_head = new ListNode(0);

        ListNode* cur = head->next;
        extra_head->next = head;
        head->next = NULL;

        while (cur)
        {
            ListNode* pre = extra_head;
            ListNode* p = extra_head->next;
            while (p != NULL && cur->val > p->val)
            {
                pre = p;
                p = p->next;
            }

            if (p == cur)
            {
                cur = cur->next;
            }
            else
            {
                ListNode* tmp = cur->next;
                pre->next = cur;
                cur->next = p;
                cur = tmp;
            }
        }

        return extra_head->next;
    }
};

void test()
{
    ListNode* head = new ListNode(-1);
    head->next = new ListNode(5);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(0);
    head->next->next->next->next->next = NULL;

    Solution s;
    ListNode* test = s.insertionSortList(head);
    cout << "test" << endl;
}