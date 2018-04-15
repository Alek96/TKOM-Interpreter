set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/Program.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionDef.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StatementBlock.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.hpp
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

        ${CMAKE_CURRENT_SOURCE_DIR}/LogicExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AndExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RelationalExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseLogicExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MathExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiplicativeExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseMathExpr.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp

        PARENT_SCOPE
        )