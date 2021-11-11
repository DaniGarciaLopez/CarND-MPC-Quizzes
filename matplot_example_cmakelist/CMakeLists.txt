cmake_minimum_required(VERSION 3.0)

project(PLT)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# main app
add_executable(main main.cpp)


# Matplotlib

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(main  ${PYTHON_LIBRARIES})