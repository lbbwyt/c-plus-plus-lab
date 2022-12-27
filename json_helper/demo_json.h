//
// Created by lbb on 2022/12/23.
//

#ifndef JSON_HELPER_DEMO_JSON_H
#define JSON_HELPER_DEMO_JSON_H

#endif //JSON_HELPER_DEMO_JSON_H
#include "JsonHelper.h"


struct DemoChildrenObject
{
    bool boolValue;
    int intValue;
    std::string strValue;
    /*JSON相互转换成员变量声明（必需）*/
    JSONCONVERT2OBJECT_MEMEBER_REGISTER(boolValue, intValue, strValue)
};

struct DemoObject
{
    bool boolValue;
    int intValue;
    std::string strValue;
    /*嵌套的支持JSON转换的结构体成员变量，数组形式*/
    std::vector< DemoChildrenObject> children;

    /*JSON相互转换成员变量声明（必需）*/
    JSONCONVERT2OBJECT_MEMEBER_REGISTER(boolValue, intValue, strValue, children)
};
