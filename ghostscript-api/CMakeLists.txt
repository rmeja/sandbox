cmake_minimum_required(VERSION 3.5)

project(ghostscript_api)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
set(SOURCE_FILES main.cpp)

include(CMakeToolsHelpers OPTIONAL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Ghostscript REQUIRED)
include_directories(${GHOSTSCRIPT_INCLUDES})

find_package (Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# target_link_libraries(${PROJECT_NAME} ${GHOSTSCRIPT_LIBRARIES} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libgs.so Threads::Threads)
