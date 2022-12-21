//
// Created by lbb on 2022/12/21.
//

#ifndef TEST_LAB_SINGLETON_H
#define TEST_LAB_SINGLETON_H

#endif //TEST_LAB_SINGLETON_H
class Singleton {
private:
    Singleton(){}
    static Singleton * p;
public:
    static Singleton *instance();
};

Singleton *Singleton::p = nullptr;


//非线性安全，考虑两个线程同时首次调用instance方法且同时检测到p是nullptr，则两个线程会同时构造一个实例给p，这将违反了单例的准则。
Singleton *Singleton::instance() {
    if (p == nullptr) {
        p = new Singleton();
    }
    return  p;
}