add_subdirectory(nodes)

set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/AST.hpp

        PARENT_SCOPE
        )

set(SOURCE_FILES
        ${SOURCE_FILES}

#        ${CMAKE_CURRENT_SOURCE_DIR}/AST.cpp

        PARENT_SCOPE
        )