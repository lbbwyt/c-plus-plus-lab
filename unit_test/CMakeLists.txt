cmake_minimum_required(VERSION 3.24)
project(unit_test)

set(CMAKE_CXX_STANDARD 17)
#set(GOOGLETEST_VERSION 1.9.0)
set(googleTestDir ./external/googletest)


add_subdirectory(
       ${googleTestDir}
)
#头文件
include_directories(
        include
        ${googleTestDir}/googletest/include
       # ${googleTestDir}/googlemock/include
)

set(TEST_SOURCE_FILE
        tests/demotest.cpp
        tests/demotest.h
        external/googletest
        )

add_executable(unit_test main.cpp)
add_executable(GTest ${TEST_SOURCE_FILE})

target_link_libraries(GTest gtest gtest_main)
#target_link_libraries(GTest gtest gmock_main)
