cmake_minimum_required(VERSION 3.22)
project(FunctionalLib)

set(CMAKE_CXX_STANDARD 20)

add_custom_target(test "./lib/Google_Tests_run")

include_directories(src)
add_subdirectory(src)
add_subdirectory(lib)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++fs")


set(SOURCE_FILES main.cpp)
add_executable(FunctionalLib_run ${SOURCE_FILES})
target_link_libraries(FunctionalLib_run FunctionalLib_lib)