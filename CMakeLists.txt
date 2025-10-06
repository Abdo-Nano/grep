cmake_minimum_required(VERSION 3.14)
project(grep LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(grep
        src/main.cpp
        src/grep.cpp
)

find_package(Catch2 3 REQUIRED)

# Tests with Catch2's main
add_executable(tests tests/main.cpp
                     tests/test_grep.cpp
                     src/grep.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
include(Catch)
catch_discover_tests(tests)
