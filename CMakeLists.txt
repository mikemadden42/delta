cmake_minimum_required(VERSION 3.10)

project(delta CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(delta delta.cc)
if (NOT MSVC)
  target_compile_options(delta PRIVATE -Wall -Wextra -pedantic)
endif()
