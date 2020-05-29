# Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree

Given a binary tree where each path going from the root to any leaf form a valid sequence, check if a given string is a valid sequence in such binary tree. 

We get the given string from the concatenation of an array of integers arr and the concatenation of all values of the nodes along a path results in a sequence in the given binary tree.

Example 1:
![img](https://assets.leetcode.com/uploads/2019/12/18/leetcode_testcase_1.png)

Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,0,1]
Output: true
Explanation: 
The path 0 -> 1 -> 0 -> 1 is a valid sequence (green color in the figure). 
Other valid sequences are: 
0 -> 1 -> 1 -> 0 
0 -> 0 -> 0
Example 2:
![img](https://assets.leetcode.com/uploads/2019/12/18/leetcode_testcase_2.png)

Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,0,1]
Output: false 
Explanation: The path 0 -> 0 -> 1 does not exist, therefore it is not even a sequence.
Example 3:
![img](https://assets.leetcode.com/uploads/2019/12/18/leetcode_testcase_3.png)

Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,1]
Output: false
Explanation: The path 0 -> 1 -> 1 is a sequence, but it is not a valid sequence.
 

Constraints:

1 <= arr.length <= 5000
0 <= arr[i] <= 9
Each node's value is between [0 - 9].

## solution

Depth-first search (DFS) with the parameters: current node in the binary tree and current position in the array of integers.深度优先遍历

When reaching at final position check if it is a leaf node.

```c++
class Solution {
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return helper(root,arr,0);
    }
    bool helper(TreeNode * node,vector<int>& arr, int pos)
    {
        if(node==NULL)
            return false;
        if(node->val!=arr[pos])
           return false;

        if(pos==arr.size()-1)//数组完了,判断当前节点是不是叶节点
            return (node->left==NULL && node->right==NULL);

        return(helper(node->left,arr,pos+1)||helper(node->right,arr,pos+1));
    }
};
```

## 参考链接

[leetCode](https://leetcode.com/explore/featured/card/30-day-leetcoding-challenge/532/week-5/3315/)