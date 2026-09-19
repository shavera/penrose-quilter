cmake_minimum_required(VERSION 3.28)

project(penrose_quilter)

add_library(penquil)
target_sources(penquil 
  PRIVATE
    main_window.cpp
    quilt_canvas.cpp
)
set_target_properties(penquil PROPERTIES CXX_STANDARD 23)

add_executable(penrose_quilter main.cpp)
target_link_libraries(penrose_quilter penquil)
