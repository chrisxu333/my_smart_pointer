cmake_minimum_required(VERSION 3.14)
project(my_smart_pointer)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${googletest_SOURCE_DIR}/googletest/include/gtest)
include_directories(./include)
file(GLOB_RECURSE SRC "*.cpp" "*.cc" "*.h")

add_executable(
  test_smart_ptr
  test.cc
)
target_link_libraries(
    test_smart_ptr
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_smart_ptr)

add_custom_target(
    run
    test_smart_ptr
)

add_custom_target(
    fmt
    COMMAND /usr/bin/clang-format
    -style=file
    -i
    ${SRC}
)