//
// Created by lbb on 2022/12/21.
//

#ifndef TEST_LAB_STACK_H
#define TEST_LAB_STACK_H

#endif //TEST_LAB_STACK_H
#include <iostream>

using namespace std;


/*
设计一个堆栈的类模板Stack，在模板中用类型参数T表示栈中存放的数据，用非类型参数MAXSIZE代表栈的大小。
*/

template<typename T, int MAXSIZE>
class  Stack {
private:
    T elem[MAXSIZE];
    int top;
public:
    Stack(){top = 0;}
    void push(T e);
    T pop();
    bool  empty(){
        if (top <= -1)
            return  1;
        else
            return  0;
    }
    void setEmpty(){
        top = -1;
    }
    bool full() {
        if (top>=MAXSIZE-1){
            return 1;
        } else
            return 0;
    }
};

template<typename T, int MAXSIZE>
void Stack<T, MAXSIZE> ::push(T e) {
    if (full()) {
        cout<<"栈已满，不能再添加元素了！";
        return;
    }
    elem[++top] = e;
}


template<typename T, int MAXSIZE>
T  Stack<T, MAXSIZE>::pop() {
    if(empty()){
        cout<<"栈已空，不能再弹出元素了！"<<endl;
        return 0;
    }
    return elem[top--];
}
