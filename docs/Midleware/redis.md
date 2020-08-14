# redis Remote Dictionary Server

[redis](https://redis.io/)

- 远程字典服务，是一个开源的使用ANSI C语言编写、支持网络、可基于内存亦可持久化的日志型、Key-Value数据库，并提供多种语言的API。

Redis is an open source(BSD licensed), in-memory data structure store, used as a database , cache and message broker. It suports data structures such as
- strings
- hashes
- lists
- sets
- sorted sets with range queries
- bitmaps(bitarray)
- hyperloglog
- geospatial indexes with radius quries
- streams

Redis has built-in 
- replication(复制回答反响)： master-slave
    > mechanisms:
    > - a master and a replica instances are well-connected
    master sends a stream of commands to the replica
    > - the link between the master and replica breaks
    the replica reconnects and attempts to proceed with a partial resynchronization--obtain the part of the stream of commonds it missed during the disconnection
    > - When a partial resynchronization is not possible
        the replica will ask for a full resynchronization. This will involve a more complex process in which the master needs to create a snapshot of all its data, send it to the replica, and then continue sending the stream of commands as the dataset changes.

- Lua scripting
    > EVAL and EVALSHA are used to evaluate scripts using the Lua interpreter built into Redis

- LRU eviction(驱逐，回收)
    > least rencently used
    redis is used as a cache

- Transactions

- different levels of on-disk persistence

- provides high availability via Redis Sentinel
    > Redis Sentinel provides high availability for Redis. In practical terms this means that using Sentinel you can create a Redis deployment that resists without human intervention certain kinds of failures.

    Redis Sentinel also provides other collateral tasks such as monitoring, notifications and acts as a configuration provider for clients.

- automatic partitioning with Redis Cluster

You can run ***atomic*** operations on these types, like 
appending to a string; 
incrementing the value in a hash; 
pushing an element to a list; 
computing set intersection, union and difference; or 
getting the member with highest ranking in a sorted set.

In order to achieve its outstanding performance, Redis works with an in-memory dataset. Depending on your use case, you can persist it either by dumping the dataset to disk every once in a while, or by appending each command to a log. Persistence can be optionally disabled, if you just need a feature-rich, networked, in-memory cache.



why Redis

数据存储

文件=====》数据库=============》内存SQL关系型
全量扫描   很多datapage        SAP HANA
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;分治、索引           内存2T
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;内存 B+ Tree        expensive
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;表很大，增删改查     存在内存数据变小
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;写变慢，并发小        指针
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;读如果索引
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;命中，仍然快
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;并发大、硬盘吞吐更不上

m ms um ns
硬盘
吞吐：100M，G
寻址时间：ms

内存：
ns

热点数据存于内存，其他数据放在硬盘==Redis
nosql key-value
速度，数据自身、
关系型的约束、范式、冗余
memcache
worker-单线程
6.x io threads
value 有类型（string list，set，hash，zset）且都有自己的本地方法

[db rank](https://db-engines.com/en/ranking)

redis.com

编译安装
wget url
tar xf filename.tar.gz
cd 
vi readme
make
yum install gcc -y
make distclean
make
安装
make PREFIX=/opt/bigdata/redis6 install
vi /etc/profile
export REDIS_HOME=/opt/bigdata/redis6
export PATH=$PATH:$REDIS_HOME/bin
source /etc/profile . /etc/profile
后台服务
cd utils
./install_server.sh


strace -ff -o path  ./redis-server

IO：nio bio epoll

使用场景
string
二进制安全--字节数组
字符串的常规操作
    对象存储、小文件（小图片）、磁盘IO换成Redis
数值操作
    秒杀：DB，
    限流
bitmap二进制操作 and or xor
    统计任意时间窗口内 用户的登录次数
        每登录一次相应bit置1
    618 登录送礼 备货 2E用户 活跃用户统计
           user
        day1 1 0 1
        day2 1 1 1
    OA 权限控制
        module 123456
        qwfand 110011
    布隆过滤器




list
双向链表
key-list（）
模拟stack，queue，array
    ltrim key 0 3
        博客评论前几页
        
数据写到Redis：其他服务器连接Redis
    数据共享、迁出
无状态


hash
hashmap
 key field1 field2
 聚合场景：eg商品详情介绍

set---操作慢----单独Redis实例help
去重，无序-rehash导致
    随机抽取：正负
    正的无重复，负有重复，可以中多份 
    推荐系统：集合操作
        共同好友：交集
        推荐好友：差集

zset
根据某字段排序
ziplist压缩表
    len（key）大于M
skip list
最多64层
随机造层
    排行榜
    有序事件：最新评论

SSM 传统项目 crud 换成Redis

use
`nc localhost 6379`
exec 9<> /dev/tcp/localhost/6379
echo "key *" >& 9

redis-cli
help @string

简介：
基于内存，速度快
K,V
worker单线程
epoll io 并发串行

1. worker 通过 epoll 查看状态
2. read client io in order
3. 计算

串行化、原子
client1 client2
R c1 C c1 W c1  RCW c2

redis持久化
    A：快照rdb(Redis DataBase)：某时刻的全量数据
    恢复速度快--适合大规模数据恢复、缺失多，数据一致性、完整性差
    在指定的时间间隔内，执行指定次数的写操作，就会把内存中的数据写入到磁盘
    B：日志 aof(Append Only Fole)
    日志方式记录每个写操作并追加到文件中
    完整 
    1、速度慢 
    2、冗余量大 --- 重写

    如果Redis只是做缓存的话可以关闭持久化

    写日志
    1、每次操作
    2、每秒钟
    3、A+B 某时刻的 rdb add 某时刻后的log

Redis事务
    Redis事务是一组命令的集合，开启事务可以一次执行多条命令，一条事务中所有的命令都会序列化
    其他用户的命令不会插入到事务执行命令序列中
    事务过程：
        - 开始事务
        - 入命令列
        - 执行事务
    注意：
        事务列队操作错误命令，则EXEC执行事务，所有命令不超过
        事务列队存在语法性错误，，列队中正确命令执行有效==》不回滚
        Watch监控某个key，开启事务期间，该key被其他客户修改，EXEC不成功

Redis架构模式[lin](https://blog.csdn.net/outdata/article/details/105582327?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase)
- 单机模式
- 主从模式
- 哨兵
- 集群模式

[jianshu](https://www.jianshu.com/p/6c970eb652d5)
[toutia0](https://www.toutiao.com/i6654866029182714382/?tt_from=weixin&utm_campaign=client_share&wxshare_count=2&from=singlemessage&timestamp=1549503562&app=news_article&utm_source=weixin&isappinstalled=0&iid=59822650971&utm_medium=toutiao_ios&group_id=6654866029182714382&pbid=6624439581881370119)

Redis 过期原理

1. 定时器：设置key过期时间的同时，设置一个定时器
2. lazydelete：过期不立即删除，当要使用的时候检查是否过期，若过期删除，返回null
3. 定时删除：每隔一定时间删除一次过期的key
os
多线程与高并发
JVM
MYSQL调优
高并发负载均衡 LVS&keeplived
Redis
zookeeper
ActiveMQ
RocketMQ
Kafka
FastDFS
Nginx
OpenSSL HTTPS
Dubbo
Docker
Kubernetes
Spring
Spring boot
NIO Netty
Hotspot

35岁【技术+管理】（保持良好的人际关系，躺赢）
硬技术和管理两条腿 
年轻选好行业，向着业务专家、顾问发展

应届生：
算法数据结构，jvm，MT（多线程），DP（设计模式），Redis，zookeeper，MySQL，NIO

spring源码，JDK源码，Linux，网络
项目
掌握架构层面的知识
