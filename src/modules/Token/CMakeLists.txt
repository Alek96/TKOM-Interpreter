set(HEADER_FILES
        ${HEADER_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/TokenType.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TokenTypeDefiner.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Token.hpp

        PARENT_SCOPE)

set(SOURCE_FILES
        ${SOURCE_FILES}

        ${CMAKE_CURRENT_SOURCE_DIR}/Token.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TokenTypeDefiner.cpp

        PARENT_SCOPE)