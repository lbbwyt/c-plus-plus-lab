cmake_minimum_required(VERSION 3.24)
#set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#        CACHE STRING "Vcpkg toolchain file")


project(json_helper)

set(CMAKE_CXX_STANDARD 17)



find_package(jsoncpp CONFIG REQUIRED)

add_executable(json_helper main.cpp JsonHelper.h demo_json.h)
target_link_libraries(${PROJECT_NAME}  PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp  )