configure_file (
    "AsvConfig.h.in"
    "${PROJECT_BINARY_DIR}/AsvConfig.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

add_library(asvlib AsvChain.cpp)
target_compile_features(asvlib PUBLIC cxx_range_for)

add_executable(asview Main.cpp)

