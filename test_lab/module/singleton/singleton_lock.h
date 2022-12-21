//
// Created by lbb on 2022/12/21.
//

#ifndef TEST_LAB_SINGLETON_LOCK_H
#define TEST_LAB_SINGLETON_LOCK_H

#endif //TEST_LAB_SINGLETON_LOCK_H
#include <iostream>

using namespace std;

class SingletonLock {
private:
    SingletonLock(){}
    static SingletonLock *p;
    static mutex lock_;
public:
    static SingletonLock * getInstance();
};

SingletonLock * SingletonLock::p = nullptr;

SingletonLock *  SingletonLock::getInstance() {

    lock_guard<mutex> guard(lock_);
    if (p == nullptr) {
        p = new SingletonLock();
    }
    return  p;
}

//lock_guard：创建时加锁，析构时解锁。
//
//作用：为了防止在线程使用mutex加锁后异常退出导致死锁的问题，建议使用lock_guard代替mutex。