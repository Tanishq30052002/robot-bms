cmake_minimum_required(VERSION 3.11)
project(params)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -fPIC -Wp,-D_GLIBCXX_ASSERTIONS")

find_package(yaml-cpp REQUIRED)

if(NOT yaml-cpp_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0 # Replace with the desired version tag
  )

  FetchContent_GetProperties(yaml-cpp)
  if(NOT yaml-cpp_POPULATED)
    FetchContent_Populate(yaml-cpp)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif(NOT yaml-cpp_FOUND)

add_library(${PROJECT_NAME} STATIC src/params.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp utils)
target_include_directories(${PROJECT_NAME} PUBLIC include)