set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/Program.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionDef.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StatementBlock.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Number.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IfStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ReturnStatement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Statement.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogicExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AndExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RelationalExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseLogicExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MathExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiplicativeExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseMathExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Expression.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/multiplicativeExpr.hpp

        PARENT_SCOPE
        )

set(SOURCE_FILES
        ${SOURCE_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Number.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector3.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp

        PARENT_SCOPE
        )