configure_file (
    "AsvConfig.h.in"
    "${PROJECT_BINARY_DIR}/AsvConfig.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

add_library(asvlib AsvChain.cpp AsvState.cpp AsvScheme.cpp AsvLoader.cpp AsvLoaderFactory.cpp AsvUri.cpp schemes/AsvCalc.cpp schemes/AsvFile.cpp)
#target_compile_features(asvlib PUBLIC cxx_range_for)

find_package(PkgConfig)
pkg_check_modules (NCURSES REQUIRED ncurses)
pkg_check_modules (MENU REQUIRED menu)

add_executable(asview Main.cpp AsvWin.cpp)
target_link_libraries(asview ${NCURSES_LIBRARIES} ${MENU_LIBRARIES} asvlib)
