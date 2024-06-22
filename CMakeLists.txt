cmake_minimum_required(VERSION 3.10)
project(LibraScan)

set(CMAKE_CXX_STANDARD 11)

# Add your C++ source files here
set(SOURCES
    main.cpp
    )

add_executable(LibraScan ${SOURCES})
