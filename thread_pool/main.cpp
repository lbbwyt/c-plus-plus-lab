#include <iostream>
#include "class/ThreadPool.h"





int main() {
    std::cout << "**************************thread_pool*****************************" << std::endl;
    ThreadPool pool(4);
    auto  result = pool.enqueue([](int answer) {return  ++answer;}, 42);
    auto  result1 = pool.enqueue([](int a, int b) {return  a + b;}, 42, 43);
    std::cout<< result.get()<<"   "<<std::endl;
    std::cout<< result1.get()<<"   "<<std::endl;
    return 0;
}
