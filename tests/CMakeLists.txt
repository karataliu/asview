find_package(PkgConfig)
pkg_check_modules (UNITTEST++ REQUIRED unittest++)

add_executable(asvtest testmain.cpp test1.cpp)
target_link_libraries(asvtest ${UNITTEST++_LIBRARIES})

enable_testing()
add_test (RunsAll asvtest)
set_tests_properties (RunsAll
  PROPERTIES PASS_REGULAR_EXPRESSION "Success")