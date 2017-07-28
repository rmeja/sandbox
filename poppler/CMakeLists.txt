cmake_minimum_required(VERSION 3.5)
project(poppler)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/extra-cmake-modules/find-modules")
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

find_package(Poppler REQUIRED)

include(CMakeToolsHelpers OPTIONAL)
include_directories(${Poppler_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${Poppler_LIBRARIES})
