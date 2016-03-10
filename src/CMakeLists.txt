configure_file (
    "asvConfig.h.in"
    "${PROJECT_BINARY_DIR}/asvConfig.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

add_executable(asview main.cpp)

