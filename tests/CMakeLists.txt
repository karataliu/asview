include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(asvtest testmain.cpp AsvChainTest.cpp AsvStateTest.cpp AsvSchemeTest.cpp AsvLoaderTest.cpp AsvUriTest.cpp)
target_link_libraries(asvtest asvlib)

enable_testing()
add_test (RunsAll asvtest)
set_tests_properties (RunsAll
  PROPERTIES PASS_REGULAR_EXPRESSION "Success")
