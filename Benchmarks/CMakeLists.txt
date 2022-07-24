
include(FetchContent)
FetchContent_Declare(
    GoogleBenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.6.1.zip
)
FetchContent_MakeAvailable(GoogleBenchmark)

add_executable(SharperC_Bench
    Source/ArrayBench.cpp
    )

target_link_libraries(SharperC_Bench
    PRIVATE
    SharperC
    benchmark_main
    )
