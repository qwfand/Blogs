# IO

## 多线程IO

使用一个`listen socket`监听端口，当一个连接到来的时候就加一个线程去处理，这种方案会在连接数量达到一定程度是不再适用。

I/O多路复用就通过一种机制，可以监视多个描述符，一旦某个描述符就绪（一般是读就绪或者写就绪），能够通知程序进行相应的读写操作。select，poll，epoll都是IO多路复用的机制。但select，poll，epoll本质上都是同步I/O，因为他们都需要在读写事件就绪后自己负责进行读写，也就是说这个读写过程是阻塞的，而异步I/O则无需自己负责进行读写，异步I/O的实现会负责把数据从内核拷贝到用户空间。

```c++
//程序绑定监听的初始化
//指定服务类型（绑定端口）
s=getaddrinfo(port)
//创建套接字
sfd=socket(..s..)
//绑定主机
bind(sfd,addr)
//sfd 用于监听
listen(sfd..)

//接收新连接 ，新连接的地址写入addr
acfd=accept(sfd,&addr...)

```

## select

```c
//select核心函数
int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
```

1. 允许程序监控多个文件描述符fd，等待直到一个或者多个文件描述符变为“ready”
2. select支持秒和微秒级别，pselect支持秒和纳秒级别
3. nfds max（3个fd_set 中的文件描述符）+1 ，如果fd有变化，之后需要手动修改该值
4. fd_set 是二进制位，每个fd对应一个bit，如果该fd就绪，该位置1，每次循环都要初始化
    所以select的文件描述符是有上限的，默认1024

5. 返回值是就绪事件数
6. 返回后需要通过（FD_ISSET())来轮询所有的fd，看起是否就绪
7. 每次调用都要把fd集合，从用户态拷贝到内核态


## poll

```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout)

 struct pollfd {
        int   fd;         /* file descriptor */
        short events;     /* requested events */
        short revents;    /* returned events */
    };
```

1. 同select
2. events是输入参数，是一个二进制位，指明fd的事件类型，
    revents是输出参数，对应事件发生后置1，还可以包含POLLERR等类型
3. 没有事件发生，也没出错就阻塞
4. timeout为milliseconds
5. 返回是基于fds数组进行轮询的
6. 文件描述符无上限
7. 输入参数和输出参数分离
8. pollfd的拷贝问题


对比：
select兼容性更好，只要支持sockect，就可以使用select
poll监控稀疏的文件描述符时性能更好
epoll监控大量文件描述符时性能好

## epoll

1.接口拆成三个函数，不需要每次都设置fd
2. 数据轻量拷贝，EPOLL_CTL_ADD将fd拷贝到内核中
3. 事件回调机制，避免使用轮询遍历，epoll_wait可以直接知道哪些fd就绪
4. fd没有上限
5. 效率不随连接数量的增加而下降
6. 连接数量较少，且连接都比较活跃的使用select和poll更好

```c
//Linux Programmer's Manual
 #define MAX_EVENTS 10
struct epoll_event ev, events[MAX_EVENTS];
int listen_sock, conn_sock, nfds, epollfd;

/* Set up listening socket, 'listen_sock' (socket(),
    bind(), listen()) */

epollfd = epoll_create(10);
if (epollfd == -1) {
    perror("epoll_create");
    exit(EXIT_FAILURE);
}

ev.events = EPOLLIN;
ev.data.fd = listen_sock;
if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
    perror("epoll_ctl: listen_sock");
    exit(EXIT_FAILURE);
}

for (;;) {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
        perror("epoll_pwait");
        exit(EXIT_FAILURE);
    }

    for (n = 0; n < nfds; ++n) {
        if (events[n].data.fd == listen_sock) {
            conn_sock = accept(listen_sock,
                            (struct sockaddr *) &local, &addrlen);
            if (conn_sock == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            setnonblocking(conn_sock);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;
            if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                        &ev) == -1) {
                perror("epoll_ctl: conn_sock");
                exit(EXIT_FAILURE);
            }
        } else {
            do_use_fd(events[n].data.fd);
        }
    }
}
```

### epoll_create()

创建一个epoll的句柄，当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。

在内核空间中申请`kzallo()`一块地址，其类型为`struct eventpoll`
其中包含了红黑树根节点（监控文件描述符）和一个就绪文件描述符列表

### epoll_ctl()

epoll的事件注册函数，它不同于select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。

add
1. 把相应socket（fd）放到epoll文件系统里file对象对应的红黑树上
2. 还会给内核中断处理程序注册一个回调函数，告诉内核，如果这个句柄的中断到了，就把它放到准备就绪list链表里

### epoll_waite()

int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
将就绪列表映射到用户空间
 
收集在epoll监控的事件中已经发送的事件。参数events是分配好的epoll_event结构体数组，epoll将会把发生的事件赋值到events数组中（events不可以是空指针，内核只负责把数据复制到这个events数组中，不会去帮助我们在用户态中分配内存）。maxevents告之内核这个events有多大，这个 maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。如果函数调用成功，返回对应I/O上已准备好的文件描述符数目，如返回0表示已超时。

### epoll工作原理

epoll同样只告知那些就绪的文件描述符，而且当我们调用epoll_wait()获得就绪文件描述符时，返回的不是实际的描述符，而是一个代表就绪描述符数量的值，你只需要去epoll指定的一个数组中依次取得相应数量的文件描述符即可，这里也使用了内存映射（mmap）技术，这样便彻底省掉了这些文件描述符在系统调用时复制的开销（加速内核与用户空间的消息传递）。

### ET（edge trigger） & LT（level Trigger）

#### LT

若就绪事件一次没有处理完，就会一直去处理。-没有处理完的事件继续放在就绪列表中。

#### ET

就绪事件只能处理一次，若没有处理完会在下次的其它事件就绪时再进行处理。而若以后再也没有就绪的事件，那么剩余的那部分数据也会随之而丢失。 
只是如果使用ET模式，就要保证每次进行数据处理时，要将其处理完，不能造成数据丢失。
ET模式只支持非阻塞的读写：为了保证数据的完整性
但倘若当前fd为阻塞的方式，那么当读完成缓冲区数据时，而对端并没有关闭写端，那么该read就会阻塞，影响其他fd以及他以后的逻辑，所以需要设置为非阻塞，当没有数据的时候，read虽然读取不到数据，但是肯定不会阻塞，那么说明此时数据已经读取完毕，可以继续处理后续逻辑了（读取其他的fd或者进入wait）


另一个本质的改进在于epoll采用基于事件的就绪通知方式。在select/poll中，进程只有在调用一定的方法后，内核才对所有监视的文件描述符进行扫描，而epoll事先通过epoll_ctl()来注册一个文件描述符，一旦基于某个文件描述符就绪时，内核会采用类似callback的回调机制，迅速激活这个文件描述符，当进程调用epoll_wait()时便得到通知。





[1 感谢江南烟雨【Linux学习】epoll详解](https://blog.csdn.net/xiajun07061225/article/details/9250579)
[2 感谢 全菜工程师小辉 彻底搞懂epoll高效运行的原理](https://baijiahao.baidu.com/s?id=1641172494287388070&wfr=spider&for=pc)
[3 感谢某简书用户](https://baijiahao.baidu.com/s?id=1653394764952522005&wfr=spider&for=pc)

#### linux programmer manual

```c
NAME
       epoll_ctl - control interface for an epoll descriptor

SYNOPSIS
       #include <sys/epoll.h>

       int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

DESCRIPTION
       This  system call performs control operations on the epoll(7) instance referred to by the file descrip‐
       tor epfd.  It requests that the operation op be performed for the target file descriptor, fd.

       Valid values for the op argument are :

       EPOLL_CTL_ADD
              Register the target file descriptor fd on the epoll instance referred to by the file  descriptor
              epfd and associate the event event with the internal file linked to fd.

       EPOLL_CTL_MOD
              Change the event event associated with the target file descriptor fd.

       EPOLL_CTL_DEL
              Remove  (deregister)  the target file descriptor fd from the epoll instance referred to by epfd.
              The event is ignored and can be NULL (but see BUGS below).

       The event argument describes the object linked to the file descriptor fd.  The  struct  epoll_event  is
       defined as :

           typedef union epoll_data {
               void        *ptr;
               int          fd;
               uint32_t     u32;
               uint64_t     u64;
           } epoll_data_t;

           struct epoll_event {
               uint32_t     events;      /* Epoll events */
               epoll_data_t data;        /* User data variable */
           };

       The events member is a bit set composed using the following available event types:

       EPOLLIN
              The associated file is available for read(2) operations.

       EPOLLOUT
              The associated file is available for write(2) operations.

       EPOLLRDHUP (since Linux 2.6.17)
              Stream  socket  peer  closed connection, or shut down writing half of connection.  (This flag is
              especially useful for writing simple code to detect peer shutdown when using Edge Triggered mon‐
              itoring.)

       EPOLLPRI
              There is urgent data available for read(2) operations.
```


#### epoll_wait的kernel代码

```c
epoll_wait()
{
    do_epoll_wait()
    {
        ep_poll(struct eventpoll *ep, struct epoll_event __user *events,
		   int maxevents, long timeout)
        {
            /**
            * ep_poll - Retrieves ready events, and delivers them to the caller supplied
            *           event buffer.
            *
            * @ep: Pointer to the eventpoll context.
            * @events: Pointer to the userspace buffer where the ready events should be
            *          stored.
            * @maxevents: Size (in terms of number of events) of the caller event buffer.
            * @timeout: Maximum timeout for the ready events fetch operation, in
            *           milliseconds. If the @timeout is zero, the function will not block,
            *           while if the @timeout is less than zero, the function will block
            *           until at least one event has been retrieved (or an error
            *           occurred).
            *
            * Returns: Returns the number of ready events which have been fetched, or an
            *          error code, in case of error.
            */
        }
    }
}
```
