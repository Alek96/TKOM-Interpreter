project(unitTest)

set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST} PARENT_SCOPE)

add_subdirectory(reader)
add_subdirectory(lexer)
add_subdirectory(printer)
add_subdirectory(token)
add_subdirectory(parser)

add_executable(${PROJECT_NAME}
        ../main.cpp
        ${SOURCE_FILES_TEST}
        )

link_test_libs(${PROJECT_NAME})
add_catch_test(${PROJECT_NAME})