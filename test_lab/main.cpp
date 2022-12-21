#include <iostream>
#include "module/singleton/singleton.h"
#include "module/mutex/read_write_test.h"
#include "map"
#include "module/data_struct/stack.h"
using namespace std;


using namespace std;
//可变参数， 个数未知， 但类型相同
void error_msg (initializer_list<string> ks) {
    for (auto item = ks.begin(); item != ks.end(); item++) {
        cout<< *item << endl ;
    }
};

//可变参数模板
void Print(){}

template<class T, class... Types>
void Print(const T& firstArg, const Types& ...args) {
    cout << firstArg<< endl;
    Print(args...);
}



int main() {
    std::cout << "*************************可变参数******************************" << std::endl;
    Print<int, char, bool>(10, 'c', true);
    std::cout << "*************************Stack******************************" << std::endl;
    Stack<int,3>  iStack;
    iStack.setEmpty();
    for(int i=0; i< 3; i++) {
        iStack.push(i);
    }
    while (1) {
        if (!iStack.empty()) {
            cout<< iStack.pop()<< endl;
        } else {
            break;
        }
    }
    std::cout << "*************************Map*******************************" << std::endl;
    /*map 读写*/
    map<string ,string> mp;
    //pair<const char*,const char*>插入
    mp.insert(pair<string ,string>("test","lbb"));

    //数组插入方式
    mp["addr"]="中国";
    for ( map<string, string>::iterator iter = mp.begin();  iter!= mp.end(); iter ++ ) {
        cout<<iter->first << iter->second<< endl;
    }
    // map 删除
    map<string, string>::iterator iter =   mp.find("addr");
    if (iter != mp.end()) {
        mp.erase(iter);
    }
    for ( map<string, string>::iterator iter = mp.begin();  iter!= mp.end(); iter ++ ) {
        cout<<iter->first << iter->second<< endl;
    }
    std::cout << "**************************singleton*****************************" << std::endl;
    cout<< Singleton::instance()<<endl;
    cout<< Singleton::instance()<<endl;
    std::cout << "**************************chrono*****************************" << std::endl;
    auto start = chrono::high_resolution_clock ::now();
    this_thread::sleep_for(chrono::milliseconds(100));
    auto end = chrono::high_resolution_clock ::now();
    int duration = (end - start).count();
    cout<< "运行时长："<< duration/1000000 <<endl;
    std::cout << "**************************rw_test*****************************" << std::endl;
    CMutexTest my_test;
    thread recv_thread(&CMutexTest::recv_msg, &my_test); // 在对下my_test上运行CMutexTest::recv_msg
    thread read_thread(&CMutexTest::read_msg, &my_test);
    std::thread::id master_thread = std::this_thread::get_id();
    std::cout << "master_thread: " << master_thread << endl;
    recv_thread.join(); // 阻塞recv_thread线程
    read_thread.join();
    return 0;
}
