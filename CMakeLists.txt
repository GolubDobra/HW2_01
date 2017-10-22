cmake_minimum_required(VERSION 3.2.2)

project(explorer VERSION 0.0.0 LANGUAGES C CXX)


set(CMAKE_CXX_COMPILER "g++-7")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCE_FILES main.cpp)
add_executable(explorer ${PROJECT_SOURCE_DIR}/${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} stdc++fs)
