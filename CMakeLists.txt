cmake_minimum_required(VERSION 3.16)
project(bsf_prototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(USERVER_ROOT "${CMAKE_SOURCE_DIR}/userver")
set(Boost_DIR "")
add_subdirectory(${USERVER_ROOT} ${CMAKE_BINARY_DIR}/userver-build)

find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE GENERATED_SOURCES "gen/model/*.cpp")
add_executable(bsf_prototype main.cpp
        ${GENERATED_SOURCES}
        UUID/IUuidGenerator.h
        UUID/UuidGenerator.cpp
        UUID/UuidGenerator.h
        PCF/DAO/InMemoryPcfBindingDao.h
        PCF/DAO/IPcfBindingDao.h
        PCF/DAO/InMemoryPcfBindingDao.cpp
        PCF/Handler/PcfBindingHandler.cpp
        PCF/Service/PcfBindingService.cpp
        PCF/Service/IPcfBindingService.h
        PCF/Service/PcfBindingService.h
        PCF/Handler/PcfBindingHandler.h)

target_link_libraries(bsf_prototype userver-core nlohmann_json::nlohmann_json)
