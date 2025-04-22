cmake_minimum_required(VERSION 3.29)
project(BSF_prototype)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "/usr/local/share/cmake")
find_package(userver REQUIRED)

add_executable(BSF_prototype main.cpp
        main.cpp
        bsf_handler.h
        hello_handler.h
        handler_request.h)

target_include_directories(BSF_prototype PRIVATE src)

target_link_libraries(BSF_prototype
        PRIVATE userver::userver
)