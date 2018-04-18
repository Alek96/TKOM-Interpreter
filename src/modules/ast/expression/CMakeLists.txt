set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/LogicExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AndExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RelationalExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseLogicExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MathExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiplicativeExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseMathExpr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/expression.hpp

        PARENT_SCOPE
        )

set(SOURCE_FILES
        ${SOURCE_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/LogicExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AndExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RelationalExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseLogicExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MathExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiplicativeExpr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseMathExpr.cpp

        PARENT_SCOPE
        )