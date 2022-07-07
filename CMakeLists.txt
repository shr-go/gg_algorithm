cmake_minimum_required(VERSION 3.0)
project(gg_algorithm)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(ExampleSrc
        example/DaryHeapExample.cc
        )

foreach(File IN LISTS ExampleSrc)
    get_filename_component(ExeName ${File} NAME_WE)
    add_executable(${ExeName} ${File})
endforeach()
