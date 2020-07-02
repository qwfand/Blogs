# Tree Traversal

## preorder

### Recursive solution 

```c++
void preorder(tree_ptr tree)
{
    if (tree){
        visit(tree);
        for each child C of tree
            preorder(C)
    }
}
```

### iterative solution

```c++
void preorder(tree+ptr tree)
{
    Stack S
    Push(tree,S)
    while S is not empty
        visit(T=Top(S))
        pop(S)
        if T->right
            push(T->right)
        if T->left
            push(T->left)
}
```

## postorder

### Recursive solution 

```c++
void postorder(tree_ptr tree)
{
    if (tree){
        for each child C of tree
            preorder(C)
        postorder(C)
    }
}
```

### iterative solution

```c++
void postorder(tree_ptr tree)
{
    Stack S
    tree_ptr pre, cur, top
    push(tree,S)
    while cur or S is not empty:
        while cur:
            push(cur,S)
            cur=cur->left
        top = Top(S)
        if top->right == NULL or top->right = pre
            visit(top)
            pre = top
            pop(S)
        else:
            cur=top->right
}
```

## level order

### Recursive solution 



### iterative solution

```c++
void levelorder(tree_ptr tree)
{
    enqueue(tree);
    while queue is not empty
        //the size of queue is the number of node in this level
        visit(T=dequeue)
        for each child C of T
            enqueue(C)
}
```

## inoder

### Recursive solution 

```c++
void inorder(tree_ptr tree)
{
    if (tree){
        inorder(tree->left)
        visit(tree);
        inorder(tree->right)
    }
}
```

### iterative solution

```c++
void inorder(tree_ptr tree)
{
    stack S
    for (;;)
    {
        for (;tree;tree=tree->left)
            push(tree,S)
        tree = Top(S)
        Pop(S)
        if(!tree)
            break
        visit(tree->ele)
        tree=tree->right
    }
}
```

## excercise

### preorder

#### [589. N-ary Tree Preorder Traversal](https://leetcode.com/problems/n-ary-tree-preorder-traversal/)

```python

class Solution:
    def preorder(self, root: 'Node') -> List[int]:
        res=[]
        def helper(node,res):
            if node:
                res.append(node.val)
                for i in node.children:
                    helper(i,res)
               
        helper(root,res)
        return res    
```

#### [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)

递归实现

```python
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        def help(node,res):
            if node:
                res.append(node.val)
                help(node.left,res)
                help(node.right,res)
                
        res=[]
        help(root,res)
        return res
```

循环实现

```python
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        stack=[]
        res=[]
        if root:
            stack.append(root)
        while stack:
            tmp=stack.pop()
            res.append(tmp.val)
            if tmp.right:
                stack.append(tmp.right)
            if tmp.left:
                stack.append(tmp.left)
        return res
```

### postorder

#### [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

递归实现

```python
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        def helper(node,res):
            if node:
                helper(node.left,res)
                helper(node.right,res)
                res.append(node.val)
        
        res=[]
        helper(root,res)
        return res
```

循环实现

```python
lass Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        stack=[]
        res=[]
        
        cur=root
        pre=top=None
        
        while stack or cur:
            while cur:
                stack.append(cur)
                cur=cur.left
            top=stack[-1]
            if top.right==None or top.right==pre:
                res.append(top.val)
                stack.pop()
                pre=top
            else:
                cur=top.right
        return res
```

### level order

#### [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

递归

```python
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        res=[]
        def helper(root,depth,res):
            if root:
                if len(res)<=depth:
                    res.append([root.val])
                else:
                    res[depth].append(root.val)
                if root.left:
                    helper(root.left,depth+1,res)
                if root.right:
                    helper(root.right,depth+1,res)
        helper(root,0,res)
        return res 
```

循环

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> v1;
        vector<vector<int>> v2;
        if(root==NULL)
            return v2;
        v1.push(root);
        while(!v1.empty())
        {
            vector<int> v3;
            //---------------//
            int a=v1.size();
            //--------------//
            for(int i=0;i<a;i++)
            {
                TreeNode *tmp=v1.front();
                v1.pop();
                v3.push_back(tmp->val);
                if(tmp->left)
                    v1.push(tmp->left);
                if(tmp->right)
                    v1.push(tmp->right);
            }
            v2.push_back(v3);
        }
         return v2;   
    }
};
```

#### [107. Binary Tree Level Order Traversal II](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/)

递归(DFS)

```python
class Solution:
    def levelOrderBottom(self, root: TreeNode) -> List[List[int]]:
        res=[]
        def helper(root,depth,res):
            if root:
                if len(res)<=depth:
                    res.append([root.val])
                else:
                    res[depth].append(root.val)
                if root.left:
                    helper(root.left,depth+1,res)
                if root.right:
                    helper(root.right,depth+1,res)
        helper(root,0,res)
        return res[::-1]
```

循环(BFS)

```c++
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> v1;
        vector<vector<int>> v2;
        if(root==NULL)
            return v2;
        v1.push(root);
        while(!v1.empty())
        {
            vector<int> v3;
            int a=v1.size();//记录该层有多少个节点
            for(int i=0;i<a;i++)
            {
                TreeNode *tmp=v1.front();
                v1.pop();
                v3.push_back(tmp->val);
                if(tmp->left)
                    v1.push(tmp->left);
                if(tmp->right)
                    v1.push(tmp->right);
            }
            v2.insert(v2.begin(),v3);
        }
         return v2;   
        
    }
};
```

#### [429. N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)

```python
class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        def helper(node,depth,res):
            if node:
                if len(res)<=depth:
                    res.append([node.val])
                else:
                    res[depth].append(node.val)
                for i in node.children:
                    helper(i,depth+1,res)
        
        res=[]
        helper(root,0,res)
        return res
```

#### [637. Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/)

waiting for you

### inorder

#### [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)

递归

```python
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        def helper(node,res):
            if node:
                helper(node.left,res)
                res.append(node.val)
                helper(node.right,res)
        
        res=[]
        helper(root,res)
        return res
```

循环

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> output;
        stack<TreeNode*> s;
        TreeNode* cur=root;
        for(;cur!=NULL||!s.empty();){
           for(;cur!=NULL;cur=cur->left){
                s.push(cur); 
            }
            cur=s.top();
            s.pop();
            output.push_back(cur->val);
            cur=cur->right;
        }
        return output;
    }
};
```


