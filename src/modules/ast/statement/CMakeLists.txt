set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/BlockStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IfStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ReturnStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Statement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AssignStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WhileStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionCall.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PrintStatement.hpp

        PARENT_SCOPE
        )

set(SOURCE_FILES
        ${SOURCE_FILES}

        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp

        PARENT_SCOPE
        )