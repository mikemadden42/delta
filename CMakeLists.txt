cmake_minimum_required(VERSION 3.10)

project(delta CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(delta delta.cc)
add_executable(delta_test delta_test.cc)
if (NOT MSVC)
  target_compile_options(delta PRIVATE -Wall -Wextra -pedantic)
  target_compile_options(delta_test PRIVATE -Wall -Wextra -pedantic)
endif()

enable_testing()
add_test(NAME delta_test COMMAND delta_test)
