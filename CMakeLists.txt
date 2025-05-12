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
        PCF/DAO/PcfBinding/InMemoryPcfBindingDao.h
        PCF/DAO/PcfBinding/IPcfBindingDao.h
        PCF/DAO/PcfBinding/InMemoryPcfBindingDao.cpp
        PCF/Handler/PcfBinding/PcfBindingBaseHandler.cpp
        PCF/Handler/PcfBinding/PcfBindingBaseHandler.h
        PCF/Service/PcfBinding/PcfBindingService.cpp
        PCF/Service/PcfBinding/PcfBindingService.h
        PCF/Service/PcfBinding/IPcfBindingService.h
        PCF/Service/PcfBinding/PcfBindingServiceComponent.h
        PCF/DAO/PcfUeBinding/IPcfUeBindingDao.h
        PCF/DAO/PcfUeBinding/InMemoryPcfUeBindingDao.cpp
        PCF/DAO/PcfUeBinding/InMemoryPcfUeBindingDao.h
        PCF/Service/PcfUeBinding/IPcfUeBindingService.h
        PCF/Service/PcfUeBinding/PcfUeBindingService.cpp
        PCF/Service/PcfUeBinding/PcfUeBindingService.h
        PCF/Service/PcfUeBinding/PcfUeBindingServiceComponent.h
        PCF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.cpp
        PCF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.h
        PCF/Handler/PcfBinding/Delete/PcfBindingDeleteHandler.h
        PCF/Handler/PcfBinding/Delete/PcfBindingDeleteHandler.cpp
        PCF/Handler/PcfBinding/Get/PcfBindingGetHandler.h
        PCF/Handler/PcfBinding/Get/PcfBindingGetHandler.cpp
        PCF/Handler/PcfBinding/Post/PcfBindingPostHandler.h
        PCF/Handler/PcfBinding/Post/PcfBindingPostHandler.cpp
        PCF/Handler/PcfUeBinding/Delete/PcfUeBindingDeleteHandler.h
        PCF/Handler/PcfUeBinding/Delete/PcfUeBindingDeleteHandler.cpp
        PCF/Handler/PcfUeBinding/Get/PcfUeBindingGetHandler.h
        PCF/Handler/PcfUeBinding/Get/PcfUeBindingGetHandler.cpp
        PCF/Handler/PcfUeBinding/Post/PcfUeBindingPostHandler.h
        PCF/Handler/PcfUeBinding/Post/PcfUeBindingPostHandler.cpp
)

target_link_libraries(bsf_prototype userver-core nlohmann_json::nlohmann_json)
