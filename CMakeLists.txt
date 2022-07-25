


add_library(SharperC
    STATIC
    Source/SharperC.cpp
    Source/Timers.cpp)

target_include_directories(SharperC
        PUBLIC
        Include
        )


add_subdirectory(Test)
add_subdirectory(Benchmarks)