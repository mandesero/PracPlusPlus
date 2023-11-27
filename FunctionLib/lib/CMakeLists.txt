project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB tests_SRC
        "*.cpp"
        )

add_executable(Google_Tests_run ${tests_SRC})

target_link_libraries(Google_Tests_run FunctionalLib_lib)
target_link_libraries(Google_Tests_run gtest gtest_main)