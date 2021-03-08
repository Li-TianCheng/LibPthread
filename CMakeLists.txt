cmake_minimum_required(VERSION 3.17)
project(LibPthread)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

aux_source_directory(./src SOURCE_FILES)

add_executable(LibPthread ${SOURCE_FILES})

target_link_libraries(LibPthread pthread)