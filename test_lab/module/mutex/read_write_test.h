//
// Created by lbb on 2022/12/21.
//

#ifndef TEST_LAB_READ_WRITE_TEST_H
#define TEST_LAB_READ_WRITE_TEST_H

#endif //TEST_LAB_READ_WRITE_TEST_H
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class CMutexTest {
public:
    void recv_msg();
    void read_msg();
private:
    vector<string>  msg_queue;
    mutex m_mutex;
};

string mock_msg() {
    return "test";
}

//模拟接收消息
void CMutexTest::recv_msg() {
    std::thread::id master_thread = std::this_thread::get_id();
    std::cout << "recv_msg_thread: " << master_thread << endl;

    while (1) {
        string msg = mock_msg();
        //使用{} 限定lock_guard作用域
        {
            lock_guard<mutex> my_lock_guard (m_mutex);
            msg_queue.push_back(msg);
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

//模拟处理消息
void CMutexTest::read_msg() {
    while (1) {
        m_mutex.lock();
        lock_guard<mutex> my_lock_guard(m_mutex, adopt_lock);
        if (!msg_queue.empty()) {
            string nsg = msg_queue.front();
            cout<< "read msg :" <<nsg<<endl;
            msg_queue.erase(msg_queue.begin());
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
}

