#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
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
        if (n == 0) return head;
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

    ListNode* partition(ListNode* head, int x) {
        ListNode* a1 = head;
        ListNode* a2 = head;

        while (a1 != NULL)
        {
            if (a1->val <= x)
            {
                swap(a1, a2);
                a2 = a2->next;
            }

            a1 = a1->next;
        }

        return head;
    }

    void swap(ListNode* a1, ListNode* a2) {
        int temp = a1->val;
        a1->val = a2->val;
        a2->val = temp;
    }

    Node* copyRandomList(Node* head) {
        if (head == NULL)
        {
            return head;
        }
        Node* p = head, * keep;
        while (p != NULL)
        {
            Node* copy_node = new Node(p->val);
            keep = p->next;
            p->next = copy_node;
            copy_node->next = keep;
            p = keep;
        }

        p = head;
        Node* copy_head = head->next;
        Node* copy_p = copy_head;
        while (p != NULL)
        {
            copy_p = p->next;
            if (p->random != NULL)
            {
                copy_p->random = p->random->next;
            }
            else
            {
                copy_p->random = NULL;
            }
            p = copy_p->next;
        }

        p = head;
        while (p != NULL)
        {
            copy_p = p->next;
            p->next = copy_p->next;
            if (copy_p->next != NULL)
            {
                copy_p->next = copy_p->next->next;
            }
            else
            {
                copy_p->next = NULL;
            }
            
            p = p->next;
        }

        copy_p->next = NULL;

        return copy_head;
    }

    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
            {
                break;
            }
        }

        if (fast == NULL || fast->next == NULL)
        {
            return NULL;
        }

        fast = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }

        return fast;
    }

    Node* flatten(Node* head) {
        if (head == NULL)
        {
            return head;
        }

        Node* dummy = new Node(-1);
        dummy->next = head;
        flatten_dfs(dummy, head);
        dummy->next->prev = NULL;
        return dummy->next;
    }

    Node* flatten_dfs(Node* prev, Node* curr)
    {
        if (curr == NULL)
        {
            return prev;
        }
        Node* child = curr->child;
        Node* keep = curr->next;
        Node* tail = curr;
        if (child != NULL)
        {
            curr->next = child;
            child->prev = curr;
            tail = flatten_dfs(curr, child);
        }

        if (keep)
        {
            tail->next = keep;
            keep->prev = tail;
            return flatten_dfs(tail, keep);
        }

        return tail;
    }

    void reorderList(ListNode* head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL)
        {
            return;
        }
        int n = 0;
        ListNode* q = head;
        while (q != NULL)
        {
            q = q->next;
            ++n;
        }

        reorderList_helper(head, n);
    }

    ListNode* reorderList_helper(ListNode* head, int len)
    {
        if (len == 1)
        {
            ListNode* outTail = head->next;
            head->next = NULL;
            return outTail;
        }

        if (len == 2)
        {
            ListNode* outTail = head->next->next;
            head->next->next = NULL;
            return outTail;
        }

        ListNode* tail = reorderList_helper(head->next, len - 2);
        ListNode* subHead = head->next;
        head->next = tail;
        ListNode* outTail = tail->next;
        tail->next = subHead;
        return outTail;
    }
};

void test()
{
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = new ListNode(4);
    head1->next->next->next->next = new ListNode(5);
    head1->next->next->next->next->next = NULL;

    Solution ss;
    ss.reorderList(head1);
}