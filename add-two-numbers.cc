#include <iostream>

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 
class Solution {
public:
    void Pushback(ListNode** res,int v)
    {
        if(*res == NULL)
        {
            *res = new ListNode(v);
            return;
        }
        ListNode* cur = *res;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new ListNode(v);
        return;
    }
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* res = NULL;
        int carry = 0;
        while(cur1 != NULL || cur2 != NULL)
        {
            int sum = 0;
            if(cur1 != NULL)
            {
                sum += cur1->val;
                cur1 = cur1->next;
            }
            if(cur2 != NULL)
            {
                sum += cur2->val;
                cur2 = cur2->next;
            }
            sum += carry;
            if(sum >= 10)
            {
                sum -= 10;
                carry = 1;
            }
            else 
            {
                carry = 0;
            }
            Pushback(&res,sum);
        }
        if(carry == 1)
        {
            Pushback(&res,1);
        }
    for(ListNode* cur = res; cur != NULL; cur = cur->next)
    {
        std::cout<<cur->val<<" ";
    }
    std::cout<<std::endl;
        return res;
    }
};

int main()
{
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(8);
    ListNode* l2 = new ListNode(0);
    Solution s;
    s.addTwoNumbers(l1,l2);
    return 0;
}
