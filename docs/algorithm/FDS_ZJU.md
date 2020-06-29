# Foundmental Data structure and algorithm

## Foundmental data structure

### linked list

### stack

### queue

### tree

### heap(priority queue)

### the disjoint set

## algorithm

### sorting

#### Insertion sort

#### Bubble sort

#### Shellsort

#### Heapsort

#### Mergesort

#### Quicksort

#### Bucket sort

### Hashing

#### Hashing function

#### Separate Chaining

#### Open Addressing

#### Rehashing

#### Extendible Hashing

## Graph Algorithms

### Representation of Graphs

- adjacency matrix

- adjacency lists

### Topological sort

Main idea:
&emsp;每次找到入度为0的vertex V（indegree=0，可以排序输出），同时与V相邻的vertex的indegree减1，如果indegree为0则加入列队或堆栈；

exercises：
- [leetcode sourse schdule](https://leetcode.com/problems/course-schedule/)
- [leetcode sourse schdule ii](https://leetcode.com/problems/course-schedule-ii/)

### Shortest-Path Algorithms

|vertet   |kwnon  | distance | Path(from)|
|:-       |:-     |:-        |:-         |
|v1       |false  |infinity  |-1           |

#### Unweighted Shortest Paths

BFS
使用一个table记录是否arrive，distance，from

#### Dijkstra's algorithm

|di：kstra|

```c
void Dijkstra(Table T)
{
    Vertext V, W;

    for( ; ; )
    {
        V = smallest unknow distance vertet
        if(V==NotAVertex)
            break;
        
        T[V].know = True;
        for each W adjacent to V
            if !T[W].known
                if( T[V].dist+Cvw < T[w].dist )
                {/*update W*/
                    Decrease( T[W].dist to T[V].dist+Cvw);
                    T[w].path=V
                }
    }
}
```

#### Graph with Neigative Edge costs

#### Acyclic Graphs

toplogical sort

#### All-Pairs Shortest Path

DP Approch

### Network Flow Problems

### Minimum Spanning Tree

#### Prim's Algorithm

grow a tree

#### Kruskal's Algorithm

every time select a min edge

### Depth-First Search

### Breadth-First Search

- 应用
    - shortest path




















