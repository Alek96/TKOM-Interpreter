cmake_minimum_required(VERSION 3.10)
project(Interpreter)

set(CMAKE_CXX_STANDARD 14)
#add_compile_options(/std:c++latest)

#if (MSVC_VERSION GREATER_EQUAL "1900")
#    include(CheckCXXCompilerFlag)
#    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
#    if (_cpp_latest_flag_supported)
#        add_compile_options("/std:c++latest")
#    endif()
#endif()

set(CATCH_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/third_party")

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/modules)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Interpreter_lib)