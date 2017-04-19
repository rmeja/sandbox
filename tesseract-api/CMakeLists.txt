cmake_minimum_required(VERSION 3.7)
project(tesseract_api)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(tesseract_api ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Tesseract REQUIRED)
find_package(Leptonica REQUIRED)
include_directories(${TESSERACT_INCLUDE_DIR} ${LEPTONICA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${TESSERACT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${LEPTONICA_LIBRARY})