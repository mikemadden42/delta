cmake_minimum_required(VERSION 3.10)

project(delta CXX)

set (CMAKE_CXX_STANDARD 14)
if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -march=native")
endif()

# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
# https://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
find_package(Boost COMPONENTS date_time)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_executable(delta delta.cc)
    target_link_libraries(delta ${Boost_LIBRARIES})
endif()
