add_subdirectory(expression)
add_subdirectory(statement)

set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/Program.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionDef.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Return.hpp

        PARENT_SCOPE
        )

set(SOURCE_FILES
        ${SOURCE_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.cpp

        PARENT_SCOPE
        )