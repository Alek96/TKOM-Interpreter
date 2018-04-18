add_subdirectory(expression)
add_subdirectory(statement)

set(SOURCE_FILES_TEST
        ${SOURCE_FILES_TEST}
        ${CMAKE_CURRENT_SOURCE_DIR}/Variable_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionDef_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/Variable_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/Variable_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/Variable_test.cpp
        PARENT_SCOPE
        )