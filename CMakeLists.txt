


add_library(SharperC
        Source/SharperC.cpp
        )

target_include_directories(SharperC
        PUBLIC
        Include
        )


add_subdirectory(Test)