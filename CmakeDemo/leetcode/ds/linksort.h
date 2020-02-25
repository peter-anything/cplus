#include<iostream>
#include<vector>

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

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;
        int k = 0;
        while (fast != NULL && k != n + 1)
        {
            fast = fast->next;
            ++k;
        }

        if (k == n)
        {
            head = head->next;
        }
        else if (k < n)
        {
            return head;
        }

        while (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* tmp = slow->next;
        slow->next = tmp != NULL ? tmp->next : NULL;

        return head;
    }

    ListNode* swapPairs(ListNode* head) {
        if (head == NULL ||  head->next == NULL)
        {
            return head;
        }

        ListNode* new_head = new ListNode(-1);
        new_head->next = head;

        ListNode* pre = new_head;
        ListNode* curr = head;

        while (curr != NULL && curr->next != NULL)
        {

            pre->next = curr->next;
            curr->next = curr->next->next;
            pre->next->next = curr;
            pre = curr;
            curr = curr->next;
        }

        return new_head->next;
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL)
        {
            return l2;
        }

        if (l2 == NULL)
        {
            return l1;
        }

        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    ListNode* merge(vector<ListNode*>& lists, int left, int right)
    {
        if (left == right)
        {
            return lists[left];
        }

        int mid = (left + right) / 2;
        ListNode* l1 = merge(lists, left, mid);
        ListNode* l2 = merge(lists, mid + 1, right);

        return mergeTwoLists(l1, l2);
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() < 0)
        {
            return NULL;
        }

        return merge(lists, 0, lists.size() - 1);
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* tmp = head, * keep;

        short counter = k;
        while (counter --)
        {
            if (tmp == NULL)
            {
                return head;
            }
            tmp = tmp->next;
        }

        counter = k;

        tmp = head;
        while (--counter)
        {
            keep = tmp->next;
            tmp->next = keep->next;
            keep->next = head;
            head = keep;
        }
        tmp->next = reverseKGroup(tmp->next, k);
    }

    static int len(ListNode* head)
    {
        int n = 0;
        while (head != NULL)
        {
            head = head->next;
            ++n;
        }
        return n;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        int n = len(head);
        k = k % n;
        if (n < 2 || k < 1)
        {
            return head;
        }
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* prev = dummy;
        for (int i = 0; i < n - k; ++i)
        {
            prev = prev->next;
        }
        ListNode* curr = prev->next;
        ListNode* old_head = dummy->next;
        dummy->next = curr;
        prev->next = NULL;
        while (curr != NULL && curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = old_head;

        return dummy->next;
    }
};

void test()
{
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(4);
    head1->next->next = new ListNode(5);
    head1->next->next->next = NULL;


    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(3);
    head2->next->next = new ListNode(4);
    head2->next->next->next = NULL;


    ListNode* head3 = new ListNode(2);
    head2->next = new ListNode(6);
    head2->next->next = NULL;

    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = NULL;
    /*head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = NULL;*/

    Solution s;
    vector<ListNode*> lists({head1, head2, head3});
    ListNode* test = s.rotateRight(head,1);
    cout << "test" << endl;
}