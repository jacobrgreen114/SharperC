cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
        GoogleTest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


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