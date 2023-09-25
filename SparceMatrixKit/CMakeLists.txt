# cmake_minimum_required(VERSION 3.16)
# project(SparceMatrixKit)
# set(CMAKE_CXX_STANDARD 20)
# add_executable(SparceMatrixKit main.cpp)
# add_subdirectory(src)
# target_link_libraries(SparceMatrixKit Rational Complex Vector Matrix)
# target_include_directories(SparceMatrixKit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

cmake_minimum_required(VERSION 3.22)
project(SparceMatrixKit)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_subdirectory(src)
add_subdirectory(lib)

set(SOURCE_FILES main.cpp)
add_executable(SparceMatrixKit_run ${SOURCE_FILES})
target_link_libraries(SparceMatrixKit_run SparceMatrixKit_lib)