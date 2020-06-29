# Toplogical Sort

使用了adjacency lists的拓扑排序，时间复杂度为O（E+V）

## 207. Course Schedule

There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
 

Constraints:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
1 <= numCourses <= 10^5

### Toplogical sort

使用拓扑排序看看有没有环即可

```python
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        graph=dict()
        indegree=[0]*numCourses
        res=[0]*numCourses
        for i in prerequisites:
            if graph.get(i[1])==None:
                graph[i[1]]=[i[0]]
            else:
                graph[i[1]].append(i[0])
                
            indegree[i[0]]+=1

        queue=[]
        for i in range(len(indegree)):
            if indegree[i] == 0:
                queue.append(i)
        count=0
        while(len(queue)>0):
            v=queue.pop(0)
            res[count]=v
            count+=1
            
            
            if graph.get(v)!=None:
                for i in graph.get(v):
                    indegree[i]-=1
                    if indegree[i] == 0:
                        queue.append(i)
        return count==numCourses
```

[207. Course Schedule](https://leetcode.com/problems/course-schedule/)

## 210. Course Schedule II

There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:

Input: 2, [[1,0]] 
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
             course 0. So the correct course order is [0,1] .
Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both     
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. 
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

### Toplogical Sort

使用拓扑排序输入每个课程的顺序

```python
class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        graph=dict()
        indegree=[0]*numCourses
        res=[0]*numCourses
        for i in prerequisites:
            if graph.get(i[1])==None:
                graph[i[1]]=[i[0]]
            else:
                graph[i[1]].append(i[0])
                
            indegree[i[0]]+=1

        queue=[]
        for i in range(len(indegree)):
            if indegree[i] == 0:
                queue.append(i)
        count=0
        while(len(queue)>0):
            v=queue.pop(0)
            res[count]=v
            count+=1
            
            
            if graph.get(v)!=None:
                for i in graph.get(v):
                    indegree[i]-=1
                    if indegree[i] == 0:
                        queue.append(i)
        if count!=numCourses:
            return []
        return res
```

[210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)

## 1494. Parallel Courses II

Given the integer n representing the number of courses at some university labeled from 1 to n, and the array dependencies where dependencies[i] = [xi, yi]  represents a prerequisite relationship, that is, the course xi must be taken before the course yi.  Also, you are given the integer k.

In one semester you can take at most k courses as long as you have taken all the prerequisites for the courses you are taking.

Return the minimum number of semesters to take all courses. It is guaranteed that you can take all courses in some way.

Example 1:

![img](https://assets.leetcode.com/uploads/2020/05/22/leetcode_parallel_courses_1.png)

Input: n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2
Output: 3 
Explanation: The figure above represents the given graph. In this case we can take courses 2 and 3 in the first semester, then take course 1 in the second semester and finally take course 4 in the third semester.
Example 2:

![img](https://assets.leetcode.com/uploads/2020/05/22/leetcode_parallel_courses_2.png)

Input: n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
Output: 4 
Explanation: The figure above represents the given graph. In this case one optimal way to take all courses is: take courses 2 and 3 in the first semester and take course 4 in the second semester, then take course 1 in the third semester and finally take course 5 in the fourth semester.
Example 3:

Input: n = 11, dependencies = [], k = 2
Output: 6
 
Constraints:

1 <= n <= 15
1 <= k <= n
0 <= dependencies.length <= n * (n-1) / 2
dependencies[i].length == 2
1 <= xi, yi <= n
xi != yi
All prerequisite relationships are distinct, that is, dependencies[i] != dependencies[j].
The given graph is a directed acyclic graph.

每个学期最多参加K门课程，问最少第三个学期可以上完所有课程

### Toplogical Sort Approch

拓扑排序的时候，先选择出度大的节点，每一次可以处理多个入度为0的节点

```python
class Solution:
    def minNumberOfSemesters(self, numCourses: int, prerequisites: List[List[int]], k: int) -> int:
        #初始化，把图存到字典里，初始化出度和入度
        graph=dict()
        indegree=[0]*(numCourses+1)
        outdegree=[0]*(numCourses+1)
        indegree[0]=1
        res=[0]*(numCourses+1)
        for i in prerequisites:
            if graph.get(i[0])==None:
                graph[i[0]]=[i[1]]
            else:
                graph[i[0]].append(i[1])
                
            indegree[i[1]]+=1
            outdegree[i[0]]+=1

        queue=[]
        ans=0
        for i in range(len(indegree)):
            if indegree[i] == 0:
                queue.append(i)
        
        while(len(queue)>0):
            # outdegree 大的课程先上
            queue.sort(key=lambda x:outdegree[x],reverse=True)
            
            #一次上K门或者所有能上的
            tmp=[]
            for i in range(min(k,len(queue))):
                tmp.append(queue.pop(0))
            
            # 更新indegree
            while len(tmp)>0:
                v=tmp.pop(0)
                if graph.get(v)!=None:
                    for i in graph.get(v):
                        indegree[i]-=1
                        if indegree[i] == 0:
                            queue.append(i)
            ans+=1
            
        return ans
        ```


