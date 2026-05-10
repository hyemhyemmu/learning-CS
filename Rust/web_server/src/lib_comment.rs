// ============================================================
// lib.rs —— 线程池的完整实现
// 负责：创建Worker、分发任务、优雅关闭
// ============================================================

use std::{
    sync::{Arc, Mutex, mpsc}, // Arc：多线程共享所有权；Mutex：互斥锁；mpsc：Channel
    thread,                   // 标准库线程
};

// ============================================================
// Job：任务的类型别名
// 本质是一个装在Box里的闭包：
//   FnOnce()   = 只执行一次的闭包（每个请求只处理一次）
//   Send       = 可以安全跨线程传递
//   'static    = 闭包里不能有短命的引用（因为不知道线程什么时候才运行）
// ============================================================
type Job = Box<dyn FnOnce() + Send + 'static>;

// ============================================================
// ThreadPool：线程池本体
// 持有所有Worker和Channel的发送端
// ============================================================
pub struct ThreadPool {
    workers: Vec<Worker>,           // 所有Worker的集合
    sender: Option<mpsc::Sender<Job>>, // Channel发送端，包在Option里
    // 为什么用Option？
    // Drop时需要把sender的所有权取出来销毁
    // 但drop(&mut self)只有&mut引用，不能直接move
    // Option::take()可以从&mut里把值取走，留下None
}

impl ThreadPool {
    /// 创建一个新的线程池
    ///
    /// size：线程数量，必须大于0
    ///
    /// # Panics
    /// size为0时panic
    pub fn new(size: usize) -> ThreadPool {
        // 0个线程的线程池没有任何意义，直接panic
        assert!(size > 0);

        // --------------------------------------------------
        // 创建Channel：一条任务传送带
        // sender：ThreadPool拿着，用来发任务
        // receiver：所有Worker共享，用来取任务
        // --------------------------------------------------
        let (sender, receiver) = mpsc::channel();

        // --------------------------------------------------
        // 把receiver包进 Arc<Mutex<>>
        //
        // 为什么需要Arc？
        //   mpsc的receiver只有一个，但4个Worker都要"拥有"它
        //   Arc = 多线程版引用计数，让多个Worker共享同一个receiver
        //
        // 为什么需要Mutex？
        //   同一时刻只能有一个Worker来取任务
        //   不然两个Worker同时取，可能拿到同一个任务（数据竞争！）
        //   Mutex = 互斥锁，同时只让一个人进来
        //
        // 合在一起：Arc<Mutex<receiver>>
        //   = 多个Worker共享 + 同时只有一个Worker能操作
        // --------------------------------------------------
        let receiver = Arc::new(Mutex::new(receiver));

        // 预分配容量，比Vec::new更高效（知道要放size个元素）
        let mut workers = Vec::with_capacity(size);

        for id in 0..size {
            // Arc::clone不是深拷贝！只是增加引用计数
            // 每个Worker拿到的是指向同一个receiver的指针
            workers.push(Worker::new(id, Arc::clone(&receiver)));
        }

        ThreadPool {
            workers,
            sender: Some(sender), // 包进Some，因为字段类型是Option
        }
    }

    /// 把一个任务交给线程池执行
    /// 调用方式和thread::spawn类似：pool.execute(|| { 你的代码 })
    pub fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'static, // 和Job的要求一致
    {
        // 把闭包装进Box，变成Job类型，才能放进Channel
        let job = Box::new(f);

        // 通过sender把Job发进Channel
        // as_ref()：把Option<Sender>变成Option<&Sender>，借用而不是移动
        // unwrap()：sender正常情况下一定存在（drop之前）
        // send().unwrap()：发送失败说明receiver端关了，直接panic
        self.sender.as_ref().unwrap().send(job).unwrap();
    }
}

// ============================================================
// Drop trait实现：ThreadPool销毁时自动触发，执行优雅关闭
// 就像C++的析构函数，出了作用域自动调用
// ============================================================
impl Drop for ThreadPool {
    fn drop(&mut self) {
        // --------------------------------------------------
        // 第一步：先销毁sender！顺序非常重要！
        //
        // sender.take() = 从Option里把sender取出来，留下None
        // drop(sender)  = 销毁sender，关闭Channel的发送端
        //
        // 效果：Channel关闭 → Worker的recv()返回Err
        //       → Worker的loop收到Err → break退出loop
        //       → Worker线程自然结束
        //
        // 为什么必须先drop sender再join？
        // 如果先join：主线程等Worker结束，Worker等新任务（recv阻塞）
        // 双方都在等对方 → 死锁！程序永远卡住
        // --------------------------------------------------
        drop(self.sender.take());

        // --------------------------------------------------
        // 第二步：等待每个Worker线程真正结束
        // drain(..) = 把workers里的元素全部取出并移走
        // join()    = "等你做完再走"，主线程阻塞直到该Worker线程结束
        // --------------------------------------------------
        for worker in self.workers.drain(..) {
            println!("Shutting down worker {}", worker.id);

            // worker.thread是Option<JoinHandle>
            // take()取出JoinHandle，留下None
            // 然后join()等线程结束
            if let Some(thread) = worker.thread {
                thread.join().unwrap();
            }
        }
    }
}

// ============================================================
// Worker：真正持有线程的结构体
// 相当于"待命的员工"，线程一直跑着，等任务来了就干活
// ============================================================
struct Worker {
    id: usize,                           // 工号，调试时用来区分不同Worker
    thread: Option<thread::JoinHandle<()>>, // 线程句柄，包在Option里（Drop时需要take出来join）
}

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Worker {
        // 创建一个新线程，线程里永远循环等任务
        // move：把receiver的Arc克隆移进闭包（闭包要拥有它，不能只借用）
        let thread = thread::spawn(move || {
            loop {
                // -----------------------------------------------
                // 取任务的关键代码：
                // receiver.lock()   → 获取Mutex锁，拿到MutexGuard
                // .unwrap()         → 锁中毒（另一个线程持锁时panic）则panic
                // .recv()           → 从Channel取一个Job，没有就阻塞等待
                //
                // 重要！let语句结束时，MutexGuard立刻被销毁 = 锁立刻释放！
                // 这样其他Worker才能来取下一个任务
                //
                // 如果用while let：锁会持续到job()执行完才释放
                // = 执行任务期间其他Worker全部傻等 = 退化成单线程！
                // -----------------------------------------------
                let message = receiver.lock().unwrap().recv();
                // 注意：recv()返回后，MutexGuard已经被drop，锁已经释放！
                // job()执行期间，其他Worker可以自由取下一个任务

                match message {
                    Ok(job) => {
                        // 收到正常任务，执行它
                        println!("Worker {id} got a job; executing.");
                        job();
                    }
                    Err(_) => {
                        // recv()返回Err = sender被drop了，Channel关闭了
                        // 这是优雅关闭的信号，不是业务错误！
                        // 和job()里面的错误是完全不同的层面
                        println!("Worker {id} disconnected; shutting down.");
                        break; // 退出loop，线程自然结束
                    }
                }
            }
        });

        Worker {
            id,
            thread: Some(thread), // 包进Some，Drop时需要take()出来join
        }
    }
}
