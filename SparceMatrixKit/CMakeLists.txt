cmake_minimum_required(VERSION 3.22)
project(SparceMatrixKit)

set(CMAKE_CXX_STANDARD 20)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    find_package(Doxygen REQUIRED)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

add_custom_target(test "./lib/Google_Tests_run")

include_directories(src)
add_subdirectory(src)
add_subdirectory(lib)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++fs")


set(SOURCE_FILES main.cpp)
add_executable(SparceMatrixKit_run ${SOURCE_FILES})
target_link_libraries(SparceMatrixKit_run SparceMatrixKit_lib)