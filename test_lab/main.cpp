#include <iostream>
#include "module/singleton/singleton.h"
using namespace std;




int main() {
    std::cout << "**************************singleton*****************************" << std::endl;
    cout<< Singleton::instance()<<endl;
    cout<< Singleton::instance()<<endl;
    std::cout << "**************************thread_pool*****************************" << std::endl;
    return 0;
}
