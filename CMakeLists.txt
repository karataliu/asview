cmake_minimum_required (VERSION 2.6)
project (Asview)

set (Asview_VERSION_MAJOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/asvConfig.h.in"
    "${PROJECT_BINARY_DIR}/asvConfig.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

add_executable(asview main.cpp)
