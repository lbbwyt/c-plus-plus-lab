#include <iostream>

#include "JsonHelper.h"
#include "demo_json.h"

int main() {

    DemoObject demoObj;
/*开始对demoObj对象的成员变量进行赋值*/
    demoObj.boolValue = true;
    demoObj.intValue = 321;
    demoObj.strValue = "hello worLd";

    DemoChildrenObject child1;
    child1.boolValue = true;
    child1.intValue = 1000;
    child1.strValue = "hello worLd child1";

    DemoChildrenObject child2;
    child2.boolValue = true;
    child2.intValue = 30005;
    child2.strValue = "hello worLd child2";

    demoObj.children.push_back(child1);
    demoObj.children.push_back(child2);


    std::string jsonStr;
    /*关键转换函数*/
    Object2Json(jsonStr, demoObj);
    std::cout << "returned json format: " << jsonStr << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
