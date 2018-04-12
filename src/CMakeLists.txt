project(Interpreter_lib)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/modules)

macro(add_header_files header_files)
    set( header_files ${header_files} ${ARGN} )
    set(HEADER_FILES
            ${HEADER_FILES}
            ${header_files}
            PARENT_SCOPE)
endmacro()

macro(add_source_files source_files)
    set(SOURCE_FILES
            ${SOURCE_FILES}
            ${source_files}
            PARENT_SCOPE)
endmacro()

add_subdirectory(modules)

set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)

add_library(${PROJECT_NAME} STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )