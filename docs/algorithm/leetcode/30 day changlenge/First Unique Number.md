# First Unique Number

You have a queue of integers, you need to retrieve the first unique integer in the queue.

Implement the FirstUnique class:

FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
int showFirstUnique() returns the value of the first unique integer of the queue, and returns -1 if there is no such integer.
void add(int value) insert value to the queue.
<pre>
Example 1:

Input: 
["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
[[[2,3,5]],[],[5],[],[2],[],[3],[]]
Output: 
[null,2,null,2,null,3,null,-1]

Explanation: 
FirstUnique firstUnique = new FirstUnique([2,3,5]);
firstUnique.showFirstUnique(); // return 2
firstUnique.add(5);            // the queue is now [2,3,5,5]
firstUnique.showFirstUnique(); // return 2
firstUnique.add(2);            // the queue is now [2,3,5,5,2]
firstUnique.showFirstUnique(); // return 3
firstUnique.add(3);            // the queue is now [2,3,5,5,2,3]
firstUnique.showFirstUnique(); // return -1

Example 2:

Input: 
["FirstUnique","showFirstUnique","add","add","add","add","add","showFirstUnique"]
[[[7,7,7,7,7,7]],[],[7],[3],[3],[7],[17],[]]
Output: 
[null,-1,null,null,null,null,null,17]

Explanation: 
FirstUnique firstUnique = new FirstUnique([7,7,7,7,7,7]);
firstUnique.showFirstUnique(); // return -1
firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7]
firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3]
firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3,3]
firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7,3,3,7]
firstUnique.add(17);           // the queue is now [7,7,7,7,7,7,7,3,3,7,17]
firstUnique.showFirstUnique(); // return 17

Example 3:

Input: 
["FirstUnique","showFirstUnique","add","showFirstUnique"]
[[[809]],[],[809],[]]
Output: 
[null,809,null,-1]

Explanation: 
FirstUnique firstUnique = new FirstUnique([809]);
firstUnique.showFirstUnique(); // return 809
firstUnique.add(809);          // the queue is now [809,809]
firstUnique.showFirstUnique(); // return -1

</pre>

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^8
1 <= value <= 10^8
At most 50000 calls will be made to showFirstUnique and add.

提示：

1. Use doubly Linked list with hashmap of pointers to linked list nodes. add unique number to the linked list. When add is called check if the added number is unique then it have to be added to the linked list and if it is repeated remove it from the linked list if exists. When showFirstUnique is called retrieve the head of the linked list.
2. Use queue and check that first element of the queue is always unique.
3. Use set or heap to make running time of each function O(logn).

## solution

理解提示1即可写出本题，使用其他暴力方法，容易超时；
用一个双向链表按顺序存储独一无二的元素，再使用一个map存储<数值，位置>，位置为双向链表的指针；
由于不知道STL里list怎样使用指针删改元素，就直接直接写双向链表了

```c++

class node {//双向链表
public:
	int a;
	node *pre;
	node *next;
};

class FirstUnique {
public:
	vector<int> num;//存储数据的vector
	map<int, node *> unique;//存储元素在双向链表中的位置
	set<int> s;//存储元素去重
	node* head, *rear;//存储双向链表的头和尾

public:
	FirstUnique(vector<int>& nums) {
		head = rear = new  node();//初始化一个dummy head
		head->next = head->pre = NULL;

		for (int i = 0; i < nums.size(); i++)
		{
			add(nums[i]);
		}
	}

	int showFirstUnique() {
		if (head->next == NULL)
			return -1;
		else
			return head->next->a;
	}

	void add(int value) {
		num.push_back(value);
		if (s.find(value) == s.end())//value元素第一次出现
		{
			struct node * tmp = new struct node;
			tmp->a = value;
			tmp->next = NULL;
			tmp->pre = rear;
			rear->next = tmp;
			rear = tmp;

			unique[value] = tmp;
			s.insert(value);
		}
		else//value元素已经存在，把双向链表中的元素酸楚
		{
			node * tmp = unique[value];
			if (tmp == rear)
			{
				rear = rear->pre;
				rear->next = NULL;
			}
			else if (tmp != NULL)
			{
				tmp->pre->next = tmp->next;
				tmp->next->pre = tmp->pre;
			}
			unique[value] = NULL;
			delete tmp;
		}
	}
};
/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
 ```

## 参考链接

[leetcode](https://leetcode.com/explore/challenge/card/30-day-leetcoding-challenge/531/week-4/3313/)
