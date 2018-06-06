cmake_minimum_required(VERSION 2.9)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab2 main.cpp class/Et.cpp class/Et.h class/Aet.cpp class/Aet.h)
target_link_libraries(lab2 freeglut opengl32 glu32)