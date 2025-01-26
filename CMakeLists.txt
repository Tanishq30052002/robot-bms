cmake_minimum_required(VERSION 3.11)
project(robot_bms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -fPIC -Wp,-D_GLIBCXX_ASSERTIONS")

set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(utils)
add_subdirectory(bms)

add_executable(${PROJECT_NAME} src/run_robot_bms.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE utils bms pthread rt)
target_include_directories(${PROJECT_NAME} PUBLIC bms/src)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}> )