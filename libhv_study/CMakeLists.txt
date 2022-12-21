cmake_minimum_required(VERSION 3.24)
project(libhv_study)


set(GOOGLETEST_VERSION 1.12.1)

set(CMAKE_CXX_STANDARD 17)



#添加头文件搜索路径
include_directories(
        /usr/local/include/hv
)

#添加库文件搜索路径
link_directories(/usr/local/lib)

add_executable(${PROJECT_NAME} main.cpp)


#该指令的作用为将目标文件与库文件进行链接。 这里根据名字， boost_thread 去寻找lib boost_thread.a文件
target_link_libraries(${PROJECT_NAME}   -lhv)




