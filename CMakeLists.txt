cmake_minimum_required(VERSION 3.10)
project(Interpreter)

set(CMAKE_CXX_STANDARD 14)

set(CATCH_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/third_party")

enable_testing()

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Interpreter_lib)