cmake_minimum_required(VERSION 3.20)
project(bsf_prototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew")

set(USERVER_ROOT "${CMAKE_SOURCE_DIR}/userver")
add_subdirectory(${USERVER_ROOT} ${CMAKE_BINARY_DIR}/userver-build)

find_package(nlohmann_json REQUIRED)

<<<<<<< Updated upstream
file(GLOB_RECURSE GENERATED_SOURCES "gen/model/*.cpp")
add_executable(bsf_prototype main.cpp
=======
file(GLOB_RECURSE GENERATED_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/gen/model/*.cpp")

add_executable(BSF2
        main.cpp
>>>>>>> Stashed changes
        ${GENERATED_SOURCES}
        UUID/IUuidGenerator.h
        UUID/UuidGenerator.cpp
        UUID/UuidGenerator.h
<<<<<<< Updated upstream
        PCF/DAO/InMemoryPcfBindingDao.h
        PCF/DAO/IPcfBindingDao.h
        PCF/DAO/InMemoryPcfBindingDao.cpp
        PCF/Handler/PcfBindingHandler.cpp
        PCF/Service/PcfBindingService.cpp
        PCF/Service/IPcfBindingService.h
        PCF/Service/PcfBindingService.h
        PCF/Handler/PcfBindingHandler.h
        PCF/Service/PcfBindingServiceComponent.h)

target_link_libraries(bsf_prototype userver-core nlohmann_json::nlohmann_json)
=======
        PCF/DAO/PcfBinding/InMemoryPcfBindingDao.h
        PCF/DAO/PcfBinding/IPcfBindingDao.h
        PCF/DAO/PcfBinding/InMemoryPcfBindingDao.cpp
        PCF/Handler/PcfBinding/PcfBindingHandler.cpp
        PCF/Handler/PcfBinding/PcfBindingHandler.h
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
        PCF/Handler/PcfUeBinding/PcfUeBindingHandler.cpp
        PCF/Handler/PcfUeBinding/PcfUeBindingHandler.h
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
>>>>>>> Stashed changes
