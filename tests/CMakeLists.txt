
macro(link_test_libs project_name)
    target_include_directories(${project_name} PRIVATE
            ${CATCH_INCLUDE_DIRS}
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/modules
            ${CMAKE_SOURCE_DIR}/test
            )

    target_link_libraries(${PROJECT_NAME} Interpreter_lib)
#    add_executable(${PROJECT_NAME} main.cpp)
endmacro()

macro(add_catch_test name)
    if (TEST_REPORT_FORMAT)
        add_test(NAME ${name} COMMAND ${name} -r ${TEST_REPORT_FORMAT} -o "${name}.test_out.xml")
    else()
        add_test(NAME ${name} COMMAND ${name})
    endif()
endmacro()

add_subdirectory(unitTest)