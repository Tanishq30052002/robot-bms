cmake_minimum_required(VERSION 3.11)
project(utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -fPIC -Wp,-D_GLIBCXX_ASSERTIONS")

add_library(${PROJECT_NAME} STATIC src/utils.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)