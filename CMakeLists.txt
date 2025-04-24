cmake_minimum_required(VERSION 3.16)
project(bsf_prototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(USERVER_ROOT "${CMAKE_SOURCE_DIR}/userver")
set(Boost_DIR "")
add_subdirectory(${USERVER_ROOT} ${CMAKE_BINARY_DIR}/userver-build)

find_package(nlohmann_json REQUIRED)

add_executable(bsf_prototype main.cpp
        PCF/PCF_dto.h
        PCF/PCF_json_bridge.h)
target_link_libraries(bsf_prototype userver-core nlohmann_json::nlohmann_json)
