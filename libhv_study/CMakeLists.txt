cmake_minimum_required(VERSION 3.23)
project(libhv_study)

set(CMAKE_CXX_STANDARD 17)
set(googleTestDir ./external/googletest)

#set(Protobuf_INCLUDE_DIRS, /usr/local/protobuf)

# 编译子文件夹的CMakeLists.txt
add_subdirectory(
        ${googleTestDir}
)



# 将.cpp/.c/.cc文件生成.a静态库
# 注意，库文件名称通常为libxxx.so，在这里只要写xxx即可
#add_library(库文件名称 STATIC 文件)

#添加头文件搜索路径
include_directories(
        /usr/local/include/hv
        /usr
        ./include
        ${googleTestDir}/googletest/include
)


#protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#grpc
find_package(gRPC CONFIG REQUIRED)
message(STATUS “Using gRPC ${gRPC_VERSION}”)






set(TEST_SOURCE_FILE
        external/googletest
        thirdparty
        tests/test.cpp tests/test.h eventLoop/main.cpp )


#添加.so/.a库文件搜索路径
link_directories(/usr/local/lib)

#add_executable(GTest ${TEST_SOURCE_FILE})
# 对add_library或add_executable生成的文件进行链接操作
# 注意，库文件名称通常为libxxx.so，在这里只要写xxx即可
#target_link_libraries(库文件名称/可执行文件名称 链接的库文件名称)
#target_link_libraries(GTest gtest gtest_main)


#find_package(jsoncpp CONFIG REQUIRED)
add_executable(${PROJECT_NAME} main.cpp module/Person.h )
#该指令的作用为将目标文件与库文件进行链接。 这里根据名字， boost_thread 去寻找lib boost_thread.a文件
#target_link_libraries(${PROJECT_NAME}  PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp  -lhv)
target_link_libraries(${PROJECT_NAME}  -lhv)

add_executable(http_client  http/main.cpp)
target_link_libraries(http_client  -lhv)



add_executable(tcp_server  tcp_server/main.cpp protorpc/generated/calc.pb.cc)
target_link_libraries(tcp_server  -lhv)


add_executable(tcp_client  tcp_client/main.cpp protorpc/generated/calc.pb.cc)
target_link_libraries(tcp_client  -lhv)


add_executable(eventLoop  eventLoop/main.cpp)
target_link_libraries(eventLoop  -lhv)

add_executable(eventLoopThread   EventLoopThread/main.cpp)
target_link_libraries(eventLoopThread  -lhv)

add_executable(EventLoopThreadPool   EventLoopThreadPool/main.cpp)
target_link_libraries(EventLoopThreadPool  -lhv)

add_executable(TimerThread   TimerThread/main.cpp)
target_link_libraries(TimerThread  -lhv)



add_executable(Protoc_Server protorpc/rpc_server/protorpc_server.cpp protorpc/generated/base.pb.cc protorpc/generated/login.pb.cc protorpc/generated/calc.pb.cc protorpc/protorpc.cpp)
target_link_libraries(Protoc_Server  -lhv ${Protobuf_LIBRARIES}  )


add_executable(Protoc_Client protorpc/rpc_client/protorpc_client.cpp protorpc/generated/base.pb.cc protorpc/generated/login.pb.cc protorpc/generated/calc.pb.cc protorpc/protorpc.cpp)
target_link_libraries(Protoc_Client  -lhv ${Protobuf_LIBRARIES}  )


add_executable(grpc_server grpc/grpc_server/main.cpp grpc/generated/helloworld.grpc.pb.cc  grpc/generated/helloworld.grpc.pb.h  grpc/generated/helloworld.pb.cc grpc/generated/helloworld.pb.h)
target_link_libraries(grpc_server ${PROTOBUF_LIBRARIES}  gRPC::grpc++)


add_executable(grpc_client grpc/grpc_client/main.cpp grpc/generated/helloworld.grpc.pb.cc  grpc/generated/helloworld.grpc.pb.h  grpc/generated/helloworld.pb.cc grpc/generated/helloworld.pb.h)
target_link_libraries(grpc_client ${PROTOBUF_LIBRARIES}  gRPC::grpc++)



#在CMakeLists.txt目录下执行以下命令
#mkdir build
#cd build
#cmake ..    #根据CMakeLists.txt生成Makefile文件
#make        #基于构建Makefile 构建程序
#make install 安装构建好的程序到指定目录，， 通常未/usr/local/bin 目录下


#find_package(jsoncpp CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)