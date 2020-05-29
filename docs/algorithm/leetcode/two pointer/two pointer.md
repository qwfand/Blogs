# Two Pointer


## 141. Linked List Cycle

判断链表是否有环

Can you solve it using O(1) (i.e. constant) memory?
[leetcode 141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)

```c++
class Solution {
public:
	bool hasCycle(ListNode *head) {
		ListNode *fast, *slow;
		/*
		if(head==NULL || head->next==NULL)
			return false;
		slow=head;
		fast=head->next;
		while(slow!=fast)
		{
			if (fast==NULL || fast->next==NULL)
				return false;
			slow=slow->next;
			fast=fast->next->next;
		}
		return true;
		*/
		slow = fast = head;
		while (fast != NULL && fast->next != NULL)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
				return true;
		}
		return false;
	}
};
```

## 142. Linked List Cycle II

判断链表是否有环，如有找出环的位置
[leetcode 142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)

假设环的长度为len，让slow pointer 先走len，fast从head开始，slow 和 fast 每次都只走一步，当他们相遇的时候slow走的路程和fast走的路程相同。

```c++
class Solution {
    public:
        ListNode * detectCycle(ListNode * head) {

            ListNode * fast ,*slow;
            fast = slow = head;
            while (fast != NULL && fast -> next != NULL) {
                fast = fast -> next -> next;
                slow = slow -> next;
                if (fast == slow)
                    break;
            }

            if (fast == NULL || fast -> next == NULL)
                return NULL;

            slow = slow -> next;
            int len = 1;
            while (slow != fast) {
                len++;
                slow = slow -> next;
            }

            slow = head;
            fast = head;
            while (len) {
                fast = fast -> next;
                len--;
            }

            while (slow != fast) {
                slow = slow -> next;
                fast = fast -> next;
                if (fast -> next == slow)
                    break;
            }

            return slow;

        }
};
```

## 876. Middle of the Linked List

寻找链表的中点
fast的速度是slow的2倍，fast到终点时，slow到中点

[leetcode](https://leetcode.com/problems/middle-of-the-linked-list/)

```c++
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        
        ListNode *fast, *slow;
        fast=slow=head;
        while(fast!=NULL && fast->next!=NULL)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;
        
    }
};
```

## 19. Remove Nth Node From End of List

[leetcode](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

移除倒数第n个元素，关键是找到倒数第n个元素，
使用两个指针，fast 和slow，让fast在slow前面n步，然后俩个一起走，当fast到最后的时候，slow刚好为倒数第n个元素。

```c++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy=new ListNode(0);
        dummy->next=head;
        ListNode * fast,*slow;
        fast=slow=dummy;
        
        while(n--)
        {
            fast=fast->next;
        }
        while(fast->next!=NULL)
        {
            fast=fast->next;
            slow=slow->next;
        }
        slow->next=slow->next->next;
        
        return dummy->next;
    }
};
```
