cmake_minimum_required(VERSION 3.0.0)

find_package(fmt)

add_executable(test test.cpp)
target_link_libraries(test fmt::fmt)
