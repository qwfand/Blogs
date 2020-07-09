# DFS for tree path

## 257. Binary Tree Paths

Given a binary tree, return all root-to-leaf paths.
Note: A leaf is a node with no children.

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def binaryTreePaths(self, root: TreeNode) -> List[str]:
        def DFS(node,path,ans):
            # path 存储到当前节点的路径，path为局部变量
            path=path+str(node.val)
            #----------------------#
            print(path,node.val,ans)

            # 如果到达叶节点加入ans
            if not node.left and not node.right:
                ans.append(path)
            if node.left:
                DFS(node.left,path+"->",ans)
            if node.right:
                DFS(node.right,path+"->",ans)
                
        ans=[]
        path=""
        if root:
            DFS(root,path,ans)
        return ans
    ```

[leetcode 257. Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/)

## 112. Path Sum

是否存在root到叶节点的路径和为一个定值

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def hasPathSum(self, root: TreeNode, sum: int) -> bool:
        '''
        def DFS(node,pre,sum,res):
            pre += node.val
            if not node.left and not node.right:
                if pre == sum:
                    res[0]= True
            else:
                if node.left:
                    DFS(node.left,pre,sum,res)
                if node.right:
                    DFS(node.right,pre,sum,res)
            
        res=[False]
        if root:
            DFS(root,0,sum,res)
        return res[0]
        '''
        if not root:
            return False

        if not root.left and not root.right and root.val == sum:
            return True
        
        sum -= root.val

        return self.hasPathSum(root.left, sum) or self.hasPathSum(root.right, sum)
```

[112. Path Sum](https://leetcode.com/problems/path-sum/)

## 113. Path Sum II

找到和为sum的 root 到 leaf的 路径

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
'''class Solution:
    def pathSum(self, root: TreeNode, sum1: int) -> List[List[int]]:
        def DFS(node,path,res):
            tmp=path[:]
            tmp.append(node.val)
            if not node.left and not node.right:
                res.append(tmp)
            if node.left:
                DFS(node.left,tmp,res)
            if node.right:
                DFS(node.right,tmp,res)
            
        path=[]
        res=[]
        if root:
            DFS(root,path,res)
        #print(res)
        ans=[i for i in res if sum(i) == sum1]
        
        return ans
        '''
class Solution:
    def pathSum(self, root: TreeNode, sum: int) -> List[List[int]]:
        if not root:
            return []
        res = []
        self.dfs(root, sum, [], res)
        return res
    
    def dfs(self, root, sum, ls, res):
        ls=ls+[root.val]
        if not root.left and not root.right and sum == root.val:
            res.append(ls)
        if root.left:
            self.dfs(root.left, sum-root.val, ls, res)
        if root.right:
            self.dfs(root.right, sum-root.val, ls, res)
```

[113. Path Sum II](https://leetcode.com/problems/path-sum-ii/)

## 437. Path Sum III

Find the number of paths that sum to a given value.

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pathSum(self, root: TreeNode, sum: int) -> int:
        def DFS(node,sum):
            if not node:
                return 0
            return pathNumFromRoot(node,sum) + DFS(node.left,sum) + DFS(node.right,sum)
            
            
        def pathNumFromRoot(node,sum):
            if not node:
                return 0
            return int(node.val==sum) + pathNumFromRoot(node.left,sum-node.val)+pathNumFromRoot(node.right,sum-node.val)
           
            
        return DFS(root,sum)
```

[437. Path Sum III](https://leetcode.com/problems/path-sum-iii/)
