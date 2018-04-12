
add_subdirectory(printer)
add_subdirectory(exception)
add_subdirectory(reader)
add_subdirectory(Token)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(AST)

set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)