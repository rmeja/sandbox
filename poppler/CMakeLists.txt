cmake_minimum_required(VERSION 3.5)
project(poppler_test)
include(CMakeToolsHelpers OPTIONAL)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)
include_directories(poppler/cpp)
add_executable(poppler_test ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/poppler/cpp/.libs/libpoppler-cpp.so)
