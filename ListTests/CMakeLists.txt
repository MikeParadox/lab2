find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
  list_tests
  ListGTests.cpp
)

target_link_libraries(
  list_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(list_tests)
