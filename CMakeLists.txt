cmake_minimum_required(VERSION 3.20)
project(bsf_prototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew")

set(USERVER_ROOT "${CMAKE_SOURCE_DIR}/userver")
add_subdirectory(${USERVER_ROOT} ${CMAKE_BINARY_DIR}/userver-build)

find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE GENERATED_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/gen/model/*.cpp")

add_executable(BSF2
        main.cpp
        ${GENERATED_SOURCES}
        UUID/IUuidGenerator.h
        UUID/UuidGenerator.cpp
        UUID/UuidGenerator.h
        BSF/DAO/PcfBinding/InMemoryPcfBindingDao.h
        BSF/DAO/PcfBinding/IPcfBindingDao.h
        BSF/DAO/PcfBinding/InMemoryPcfBindingDao.cpp
        BSF/Handler/PcfBinding/PcfBindingBaseHandler.cpp
        BSF/Handler/PcfBinding/PcfBindingBaseHandler.h
        BSF/Service/PcfBinding/PcfBindingService.cpp
        BSF/Service/PcfBinding/PcfBindingService.h
        BSF/Service/PcfBinding/IPcfBindingService.h
        BSF/Service/PcfBinding/PcfBindingServiceComponent.h
        BSF/DAO/PcfUeBinding/IPcfUeBindingDao.h
        BSF/DAO/PcfUeBinding/InMemoryPcfUeBindingDao.cpp
        BSF/DAO/PcfUeBinding/InMemoryPcfUeBindingDao.h
        BSF/Service/PcfUeBinding/IPcfUeBindingService.h
        BSF/Service/PcfUeBinding/PcfUeBindingService.cpp
        BSF/Service/PcfUeBinding/PcfUeBindingService.h
        BSF/Service/PcfUeBinding/PcfUeBindingServiceComponent.h
        BSF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.cpp
        BSF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.h
        BSF/Handler/PcfBinding/Delete/PcfBindingDeleteHandler.h
        BSF/Handler/PcfBinding/Delete/PcfBindingDeleteHandler.cpp
        BSF/Handler/PcfBinding/Get/PcfBindingGetHandler.h
        BSF/Handler/PcfBinding/Get/PcfBindingGetHandler.cpp
        BSF/Handler/PcfBinding/Post/PcfBindingPostHandler.h
        BSF/Handler/PcfBinding/Post/PcfBindingPostHandler.cpp
        BSF/Handler/PcfUeBinding/Delete/PcfUeBindingDeleteHandler.h
        BSF/Handler/PcfUeBinding/Delete/PcfUeBindingDeleteHandler.cpp
        BSF/Handler/PcfUeBinding/Get/PcfUeBindingGetHandler.h
        BSF/Handler/PcfUeBinding/Get/PcfUeBindingGetHandler.cpp
        BSF/Handler/PcfUeBinding/Post/PcfUeBindingPostHandler.h
        BSF/Handler/PcfUeBinding/Post/PcfUeBindingPostHandler.cpp
)

target_link_libraries(BSF2
        PRIVATE
        userver-core
        nlohmann_json::nlohmann_json
)

set_target_properties(BSF2 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)