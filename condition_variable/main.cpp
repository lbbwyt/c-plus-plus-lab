#include <iostream>
#include <thread>


//condition_variable 是C++11提供的条件变量，可用于同时阻塞一个线程或多个线程。
// 一般的，生产者线程利用支持std::mutex的std::lock_guard/std::unique_lock修改共享变量后，并通知condition_variable。
// 消费者线程获取同一个std::mutex(std::unique_lock所持有)，并调用std::condition_variable的wait, wait_for, or wait_until。
// wait操作会释放互斥量，同时挂起该线程。当条件变量收到通知、超时到期或发生虚假唤醒时，线程被唤醒，互斥量也被原子地重新获取。

std::mutex mutex;
std::condition_variable cv;
std::string  data;
bool  ready = false;
bool  processed = false;


void worker_thread() {
    std::unique_lock lock(mutex);
    cv.wait(lock, []{return ready;});

    std::cout<< "worker process start process data" <<std::endl;
    data += " after process";
    processed = true;

    lock.unlock();
    cv.notify_one();

}


int main() {
    std::thread worker(worker_thread);
    data = "Example data";
    // 发送准备就绪信号给工作线程
    {
        std::lock_guard lock(mutex);
        ready = true;
        std::cout<<"main thread signals data ready for processing\n";
    }
    cv.notify_one();


    //等待工作线程完成任务
    {
        std::unique_lock lock(mutex);
        cv.wait(lock, [] {return  processed;});
    }

    std::cout<< "back to main thread, data = " << data << std::endl;

    worker.join();
}
