cmake_minimum_required(VERSION 3.14)
project(matrix)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(inc)

add_executable(
  vector_test
  test/vector_test.cpp
)

add_executable(
    matrix_test
    test/matrix_test.cpp
)

add_executable(
    matrix
    main.cpp
)

target_link_libraries(
    vector_test
    GTest::gtest_main
)

target_link_libraries(
    matrix_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_test)
gtest_discover_tests(matrix_test)