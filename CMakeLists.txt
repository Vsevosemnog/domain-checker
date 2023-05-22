cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(domain-checker)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(domain-checker ${all_SRCS})

target_link_libraries(domain-checker dpp cpprest boost_system crypto ssl)