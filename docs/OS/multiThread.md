# Java 多线程

## CAS硬件实现

CAS compare and sawap
    lock if is multiCPU （lock 后执行cmpxchg其他CPU不可以打断）
    asm cmpxchg
ABA 问题-加版本号
AtomicInterger

JOL maven java 对象解析工具

## 锁升级过程

new xx()
对象头 8
     above markWord
类型指针 4
  
（数组长度if 数组）
实例数据（成员变量）
对齐 8整除

synchronized（o）
记录在markWord里

new 偏向锁 轻量级锁 （无锁、自旋锁、自适应锁）-重量级锁
 
 第一个线程来的时候
 偏向锁：54bit 当前线程的指针 javaThread *  
 有线程竞争
 轻量级锁：撤销偏向锁，加上指向线程栈中的lockrecord的指针（CAS）
 自旋大于10次or自旋线程超过CPU核心数的一半 1.6加入自适应自旋，jvm自己控制
 重量级锁mutex（内核）：指向互斥量的指针
    mutex互斥量中有一个队列，其他线程不消耗CPU，排队叫号

StringBuffer 线程安全

## syncronized

1. java code：syschronized
2. 字节码：monitorenter monitorexit
3. jvm执行过程自动升级
4. lock comxchg

## volitale 与内存屏障

保证线程可见性

    变量复制到本地

阻止指令重排序

hdis

热点代码会编译成机器语言


超线程

线程：CPU执行的基本单位

一个ALU对应多个PC、Register
四核八线程

cache line 64字节
缓存行对齐 disruptor

系统底层如何实现数据一致性
1. MESI如果能解决就MESI
2. 不能锁死总线
3. JVM不是这样的
MESI Cache 一致性性协议

系统底层如何保证有序性

1. 内存屏障sfence mfence ifence等系统原句
2. 锁总线

volatile 如何禁止指令重排序

1. volition i
2. ACC_Volatile
3. JVM的内存屏障
4. Hotspot
    lock

内存屏障：屏障两边的指令不可以重排，保障有序，JSR

DCL Double Check Lock的单例需要volitale防止指令重排序，得到半初始对象


单例，类的对象在内存中只有一个




对象的创建过程：

```java
class T{
    int m=8;
}

T t=new T()

asm
new #2 <T> 分配内存 m=0
dup
invokespecial #3 <T.<init>> 调用构造方法
astore_1 t建立关联
return
```

强软弱虚引用类型

软引用内存分配20m
    缓存非常合适，内存不够用就gc
弱引用
    一次性
    防止内存泄漏

虚引用
    管理堆外内存-NIO neetty zero-copy

OOM

AQS

ThreadLocal 线程本地变量
    spring @ Translation
    数据库连接放在threadlocal里



## Runnable

Runnable 接口中只有一个run方法

Thread

public class Thread
extends Object
implements Runnable

官方文档里有两种使用线程的方法，1.直接继承Tread类， 2. 实现Runnable接口，再创建Tread实例

```java
class PrimeThread extends Thread {
    long minPrime;
    PrimeThread(long minPrime) {
        this.minPrime = minPrime;
    }

    public void run() {
        // compute primes larger than minPrime
        . . .
    }
}
//

PrimeThread p = new PrimeThread(143);
p.start();
```

```java
class PrimeRun implements Runnable {
    long minPrime;
    PrimeRun(long minPrime) {
        this.minPrime = minPrime;
    }

    public void run() {
        // compute primes larger than minPrime
        . . .
    }
}

PrimeRun p = new PrimeRun(143);
new Thread(p).start();
```

多线程交替输出AB

volitale实现

```java
public class PrintAB3 {
    volatile static boolean  Running = true;

    void PrintA(){
        for (int i=0;i<10;i++) {
            while (!Running) {
            }
            System.out.print("A");
            Running = false;
        }
    }

    void PrintB() {
        for (int i=0;i<10;i++) {
            while (Running) {
            }
            System.out.print("B");
            Running = true;
        }
    }

    public static void main(String[] args){
        PrintAB3 printAB3 = new PrintAB3();
        new Thread(printAB3::PrintA,"thread a:").start();
        new Thread(printAB3::PrintB,"thread b:").start();
    }
}
```

## Callable

## 线程池

为什么要使用线程池

1. 降低资源消耗，重复利用已创建的线程降低线程创建和销毁造成的消耗
2. 提高响应速度
3. 提高线程的可管理性，线程是稀缺资源，如果无限制地创建，不仅会消耗系统资源，还会降低系统的稳定性，使用线程池可以进行统一分配、调优和监控。

int corePoolSize
线程池的核心线程数，当提交一个任务，线程池创建一个新任务，知道当前线程数等于corePoolSize
如果当前线程数为corePoolSize，继续提交的任务保存到阻塞队列中，等待被执行
如果执行了线程池的平restartAllCoreThread，提前创建并启动所有核心线程

int maximumPoolSize
线程池中运行的最大线程数。如果当前阻塞队列满了，且继续提交任务，则创建新的线程执行任务，前提是当前线程数小于maximumPoolSize

long keepAliveTime
线程空闲时的存活时间，即当线程没有任务执行时，继续存活的时间。默认情况下，该参数只在线程数大于corePoolSize时才有用，且只对corePool以外的线程有用。

BlockingQueue< Runnable > workQueue
用于保存等待执行的任务的阻塞队列。当线程池中的线程数超过它的corePoolSize的时候，线程会进入阻塞队列进行阻塞等待。一般来说，我们应该尽量使用有界队列，因为使用无界队列作为工作队列会对线程池带来如下影响。

1. 当线程池中的线程数达到corePoolSize后，新任务将在无界队列中等待，因此线程池中的线程数不会超过corePoolSize。
2. 由于1，使用无界队列时maximumPoolSize将是一个无效参数。
3. 由于1和2，使用无界队列时keepAliveTime将是一个无效参数。
4. 更重要的，使用无界queue可能会耗尽系统资源，有界队列则有助于防止资源耗尽，同时即使使用有界队列，也要尽量控制队列的大小在一个合适的范围。所以我们一般会使用，ArrayBlockingQueue、LinkedBlockingQueue、SynchronousQueue、PriorityBlockingQueue。

ThreadFactory threadFactory
创建线程的工厂，通过自定义的线程工厂可以给每个新建的线程设置一个具有识别度的线程名，当然还可以更加自由的对线程做更多的设置，比如设置所有的线程为守护线程。
Executors静态工厂里默认的threadFactory，线程的命名规则是“pool-数字-thread-数字”。

RejectedExecutionHandler
线程池的饱和策略，当阻塞队列满了，且没有空闲的工作线程，如果继续提交任务，必须采取一种策略处理该任务，线程池提供了4种策略：

AbortPolicy：直接抛出异常，默认策略。
CallerRunsPolicy：用调用者所在的线程来执行任务。
DiscardOldestPolicy：丢弃阻塞队列中靠最前的任务，并执行当前任务。
DiscardPolicy：直接丢弃任务。
当然也可以根据应用场景实现RejectedExecutionHandler接口，自定义饱和策略，如记录日志或持久化存储不能处理的任务。

线程池的工作机制
如果当前运行的线程少于corePoolSize，则创建新线程来执行任务（注意，执行这一步骤需要获取全局锁）。
如果运行的线程等于或多于corePoolSize，则将任务加入BlockingQueue。
如果无法将任务加入BlockingQueue（队列已满），则创建新的线程来处理任务。
如果创建新线程将使当前运行的线程超出maximumPoolSize，任务将被拒绝，并调用RejectedExecutionHandler.rejectedExecution()方法。

Executors（预定义线程池）
无继承关系，通过调用静态方法返回不同的ExecutorService。

newFixedThreadPool
适用于为了满足资源管理的需求，而需要限制当前线程数量的应用场景，它适用于负载比较重的服务器。

corePoolSize和maximumPoolSize都被设置为创建FixedThreadPool时指定的参数nThreads。
keepAliveTime设置为0L，意味着多余的空闲线程会被立即终止。
FixedThreadPool使用有界队列LinkedBlockingQueue作为线程池的工作队列，队列的容量为Integer.MAX_VALUE（太大，很有可能把内存和CPU撑爆）。
newSingleThreadExecutor
适用于于需要保证顺序地执行各个任务，并且在任意时间点，不会有多个线程是活动的应用场景。

corePoolSize和maximumPoolSize被设置为1。
其他参数与FixedThreadPool相同。

适用于执行很多的短期异步任务的小程序，或者是负载较轻的服务器。
[csdn](https://blog.csdn.net/weixin_44367006/article/details/98839996)
corePoolSize被设置为0，即corePool为空
maximumPoolSize被设置为Integer.MAX_VALUE。
keepAliveTime设置为60L，意味着CachedThreadPool中的空闲线程等待新任务的最长时间为60秒，空闲线程超过60秒后将会被终止。
CachedThreadPool使用没有容量的SynchronousQueue作为线程池的工作队列。如果主线程提交任务的速度高于maximumPool中线程处理任务的速度时，CachedThreadPool会不断创建新线程。极端情况下，会因为创建过多线程而耗尽CPU和内存资源。

线程池刚创建时，里面没有一个线程。任务队列是作为参数传进来的。不过，就算队列里面有任务，线程池也不会马上执行它们。
当调用 execute() 方法添加一个任务时，线程池会做如下判断：
如果正在运行的线程数量小于 corePoolSize，那么马上创建线程运行这个任务；
如果正在运行的线程数量大于或等于 corePoolSize，那么将这个任务放入队列；
如果这时候队列满了，而且正在运行的线程数量小于 maximumPoolSize，那么还是要创建非核心线程立刻运行这个任务；
如果队列满了，而且正在运行的线程数量大于或等于 maximumPoolSize，那么线程池会抛出异常RejectExecutionException。
当一个线程完成任务时，它会从队列中取下一个任务来执行。
当一个线程无事可做，超过一定的时间（keepAliveTime）时，线程池会判断，如果当前运行的线程数大于 corePoolSize，那么这个线程就被停掉。所以线程池的所有任务完成后，它最终会收缩到 corePoolSize 的大小。

FixedThreadPool SingleThreadPool任务列队 Integer.MAX_VALUE

CachedThreadPool ScheduledThreadPool 允许创建的线程数为Integer.MAX_VALUE
