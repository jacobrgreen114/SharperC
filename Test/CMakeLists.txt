cmake_minimum_required(VERSION 3.20)



add_executable(SharperC_Test
        Source/ArrayTest.cpp
        Source/ListTest.cpp)

target_link_libraries(SharperC_Test
        PRIVATE
        SharperC
        gtest_main
        )

include(GoogleTest)
gtest_discover_tests(SharperC_Test)