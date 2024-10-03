cmake_minimum_required(VERSION 3.29)
project(SimplexTASK)

set(CMAKE_CXX_STANDARD 20)

add_executable(SimplexTASK main.cpp
        simplex.cpp
        tools/matrix.cpp
        tools/math.cpp
        tools/elimination.cpp
)
