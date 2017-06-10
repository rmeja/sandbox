cmake_minimum_required(VERSION 3.5)
project(tesseract_api)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
include(CMakeToolsHelpers OPTIONAL)
find_package(Boost 1.58 REQUIRED COMPONENTS filesystem REQUIRED)
find_package(Tesseract REQUIRED)
find_package(Leptonica REQUIRED)
include_directories(
        ${Boost_INCLUDE_DIRS}
        ${TESSERACT_INCLUDE_DIRS}
        ${LEPTONICA_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src)

set(SOURCE_FILES main.cpp)
add_executable(tesseract_api ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${TESSERACT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${LEPTONICA_LIBRARY})

set(SOURCE_TEST_FILES test/octachore-test.cpp src/octachore.cpp)
add_executable(octachore-test ${SOURCE_TEST_FILES})
target_link_libraries(octachore-test ${Boost_LIBRARIES})
target_link_libraries(octachore-test ${TESSERACT_LIBRARY})
target_link_libraries(octachore-test ${LEPTONICA_LIBRARY})
