cmake_minimum_required(VERSION 3.16)
project(Download_Manager LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Network
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    Download_Manager.ui
    Download_Manager.h
    Download_Manager.cpp

    DownloadItemWidget.ui
    DownloadItemWidget.h
    DownloadItemWidget.cpp

    DownloadManager.h
    DownloadManager.cpp

    DownloadTask.h
    DownloadTask.CPP
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Network
)

