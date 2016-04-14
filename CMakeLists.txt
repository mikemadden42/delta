cmake_minimum_required(VERSION 2.8)

project(delta CXX)

add_definitions(-Wall -O2 -std=c++11 -march=native)

# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
find_package(Boost COMPONENTS date_time)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(delta delta.cc)
    target_link_libraries(delta ${Boost_LIBRARIES})
endif()
