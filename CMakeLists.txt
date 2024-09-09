cmake_minimum_required(VERSION 3.26)
project(GameQt)

add_subdirectory(GameFourInARow)

message(${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

