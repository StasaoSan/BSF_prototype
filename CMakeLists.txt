cmake_minimum_required(VERSION 3.23)
project(bsf_prototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(APP_TARGET bsf2)


set(USERVER_USE_STATIC_LIBS ON)
find_package(userver COMPONENTS core REQUIRED)
userver_setup_environment()

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost COMPONENTS regex REQUIRED)

include(FetchContent)
FetchContent_Declare(
	nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG 68c25aec608db272fd62f8eae2c34fb5e73a1af5 
)
FetchContent_MakeAvailable(nlohmann_json)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE GENERATED_SOURCES_NBSF CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/gen/nbsf-management/model/*.cpp")
file(GLOB_RECURSE MAIN_SOURCES_NBSF CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/BSF/*.cpp")

add_executable(${APP_TARGET})

target_sources(${APP_TARGET} PRIVATE
	main.cpp 
	UUID/UuidGenerator.cpp 
	${GENERATED_SOURCES_NBSF}
	${MAIN_SOURCES_NBSF}
)

target_link_libraries(${APP_TARGET}
	PRIVATE
	userver::core
	Boost::regex
	nlohmann_json::nlohmann_json
)

set_target_properties(${APP_TARGET} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
