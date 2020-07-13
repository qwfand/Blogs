# Construct Binary Tree Series

树有前中后层序遍历方法，给出其中的一种或几种，你能构建出此棵树来吗？

## 105. Construct Binary Tree from Preorder and Inorder Traversal

涉及到中序的遍历会比较好理解一些，比如
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
前序遍历的3是根节点
在中序遍历中找到3的位置，左边是左子树，右边为有子树

```python
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        def helper(preStart,inStart,inEnd,preorder,inorder):
            if preStart > len(preorder) - 1 or inStart > inEnd:
                return None
            root=TreeNode(preorder[preStart])
            
            index = 0 #index of current root in inorder
            for i in range(inStart,inEnd+1):
                if inorder[i] == root.val:
                    index = i
                    break
            root.left = helper(preStart + 1, inStart, index - 1,preorder,inorder)
            #(index - inStart + 1) is the length of left tree of current root so 
            root.right = helper(preStart + index - inStart + 1,index + 1,inEnd,preorder,inorder)
            return root
        return helper(0, 0, len(inorder), preorder, inorder)
```

## 106. Construct Binary Tree from Inorder and Postorder Traversal

```python
class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> TreeNode:
        def helper(inStart,inEnd,postEnd,inorder,postorder):
            if postEnd < 0 or inStart > inEnd:
                return None
            root = TreeNode(postorder[postEnd])
            index = 0 # the index of current node in inorder
            for i in range(inStart,inEnd+1):
                if inorder[i] == root.val:
                    index = i
                    break
            
            # inEnd - index + 1 is the length of right root
            #print("before root")
            #print(inStart,inEnd,index)
            #print("root"+str(root.val))
            #print(inStart,index - 1, postEnd - (inEnd - index + 1) )
            #print(index + 1, inEnd, postEnd - 1)
            root.left = helper(inStart,index - 1, postEnd - (inEnd - index + 1) , inorder, postorder)
            root.right = helper(index + 1, inEnd, postEnd - 1, inorder, postorder)
            
            return root
        
        return helper(0,len(inorder) - 1, len(postorder) - 1    , inorder, postorder)
```
