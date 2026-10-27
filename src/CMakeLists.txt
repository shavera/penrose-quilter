cmake_minimum_required(VERSION 3.28)

project(penrose_quilter)

add_subdirectory(app)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(penrose_quilter main.cpp)
target_link_libraries(penrose_quilter penquil_app Qt6::Widgets)
