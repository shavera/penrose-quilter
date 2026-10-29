cmake_minimum_required(VERSION 3.28)

find_package(Qt6 REQUIRED COMPONENTS Core StateMachine Widgets)

qt_standard_project_setup()

add_library(penquil_app STATIC)
target_sources(penquil_app
        PRIVATE
        MainWindow.cpp
        QuiltCanvas.cpp
        QuiltView.cpp
        SizeWidget.cpp
        Tiles.cpp
        TileSelector.cpp
        ViewStateMachine.cpp

        include/app/MainWindow.h
        QuiltCanvas.h
        QuiltView.h
        SizeWidget.h
        Tiles.h
        TileSelector.h
        ViewStateMachine.h

        MainWindow.ui
        TileSelector.ui
        SizeWidget.ui
)
target_include_directories(penquil_app PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(penquil_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(penquil_app PROPERTIES CXX_STANDARD 23)
target_link_libraries(penquil_app PRIVATE Qt6::Widgets Qt6::StateMachine)


