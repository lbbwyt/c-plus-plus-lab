//
// Created by lbb on 2022/12/20.
//

#ifndef C_PLUS_PLUS_LAB_THREADPOOL_H
#define C_PLUS_PLUS_LAB_THREADPOOL_H

#endif //C_PLUS_PLUS_LAB_THREADPOOL_H

#include <iostream>
#include <future>
#include "queue"

class ThreadPool {
public:
    ThreadPool(size_t);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args )
    -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();

private:
    //工作线程池
    std::vector<std::thread> workers;
    //任务队列
    std::queue<std::function<void()> > tasks;

    //同步器
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

};


//构造函数启动工作线程（使用lamada的方式）， 并插入队列
inline  ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i< threads; i++) {
        workers.emplace_back( //和push_back相比， emplace_back()在实现时，则是直接在容器的尾部创建这个元素，省去了拷贝或移动元素的过程。
                [this]
                {
                    for (;;) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock, [this]{
                                return this->stop||!this->tasks.empty();
                            });
                            if (this-> stop && this->tasks.empty()) {
                                return ;
                            }
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        task();
                    }
                }
        );
    }
}

//工作任务入队列，

template<class F, class... Args>
auto  ThreadPool::enqueue(F&& f, Args&&... args )
-> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()> > (
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );
    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task](){
            (*task)();
        });
    }

    condition.notify_one();
    return  res;

}


inline  ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}