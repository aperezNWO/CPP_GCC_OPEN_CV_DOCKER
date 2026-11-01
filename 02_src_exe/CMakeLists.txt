cmake_minimum_required(VERSION 3.18)
project(OpenCvApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv4)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} OpenCvApp.cpp Algorithm.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "OpenCvAppV2")

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::OPENCV Threads::Threads)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0A00)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 crypt32)
endif()