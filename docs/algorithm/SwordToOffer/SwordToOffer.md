# 剑指offer系列

### 两个stack模拟queue

思路：stack1只接受元素
出栈时，要拿到stack1最下面的元素，一直pop，pop的同时，这些元素push到stack2，stack2中top的元素即为queue中pop的元素，pop之后，再把stack2中的元素放入stack1即可

```c++
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int ans;
        while (!stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        ans = stack2.top();
        stack2.pop();
       
        while(!stack2.empty())
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        return ans;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```

### 二叉树深度

```c++
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        return FindDepth(pRoot, 0);
    
    }
    int FindDepth(TreeNode *node, int depth)
    {
        if (node == nullptr)
            return depth;
        else
            return max(FindDepth(node->left, depth + 1), FindDepth(node->right, depth + 1));
    }
};
```

### 二叉树镜像

```c++
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        helper(pRoot);
    }
    void helper(TreeNode *node)
    {
        if (node == nullptr)
            return;
        else{
            TreeNode *tmp = node->left;
            node->left = node->right;
            node->right = tmp;
            helper(node->left);
            helper(node->right);
        }
    }
};
```