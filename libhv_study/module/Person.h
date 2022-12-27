//
// Created by lbb on 2022/12/22.
//

#ifndef LIBHV_STUDY_PERSON_H
#define LIBHV_STUDY_PERSON_H

#endif //LIBHV_STUDY_PERSON_H
#include "iostream"

#include "JsonHelper.h"



class Person {
private:
    std::string name;
    int sex;
public:
    Person(){};
    Person(std::string name, int sex){
        name = name;
        sex = sex;
    };
    Person * createFromJson(std::string json_str)   {
        Person * p = new Person();

        return p ;
    }



};