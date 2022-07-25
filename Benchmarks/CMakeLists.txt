

add_executable(SharperC_Bench
    Source/ArrayBench.cpp
    )

target_link_libraries(SharperC_Bench
    PRIVATE
    SharperC
    benchmark_main
    )
