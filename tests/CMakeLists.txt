find_package(PkgConfig)
#pkg_check_modules (UNITTEST++ REQUIRED unittest++)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(asvtest testmain.cpp AsvChainTest.cpp AsvStateTest.cpp)
target_link_libraries(asvtest unittest++ asvlib)

enable_testing()
add_test (RunsAll asvtest)
set_tests_properties (RunsAll
  PROPERTIES PASS_REGULAR_EXPRESSION "Success")