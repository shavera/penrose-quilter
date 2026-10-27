cmake_minimum_required(VERSION 3.28)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

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

        include/app/MainWindow.h
        QuiltCanvas.h
        QuiltView.h
        SizeWidget.h
        Tiles.h
        TileSelector.h

        MainWindow.ui
        TileSelector.ui
        SizeWidget.ui
)
target_include_directories(penquil_app PUBLIC include)
set_target_properties(penquil_app PROPERTIES CXX_STANDARD 23)
target_link_libraries(penquil_app PRIVATE Qt6::Widgets)


