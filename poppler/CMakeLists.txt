cmake_minimum_required(VERSION 3.5)
project(poppler)
include(CMakeToolsHelpers OPTIONAL)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)
include_directories(poppler/cpp)
add_executable(poppler ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/poppler/cpp/.libs/libpoppler-cpp.so)
