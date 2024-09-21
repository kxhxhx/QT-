cmake_minimum_required(VERSION 3.5)

project(EIChange VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)


INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EIChange
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET EIChange APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(EIChange SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(EIChange
            ${PROJECT_SOURCES}
            EIChange.qrc
            eichangesettings.h eichangesettings.cpp

            viewlayout.h viewlayout.cpp viewlayout.ui
            eichangefiles.h eichangefiles.cpp

            eichangetreeview.h eichangetreeview.cpp

            eichangebasewidget.h eichangebasewidget.cpp
            eichangebutton.h eichangebutton.cpp
            eichangeslider.h eichangeslider.cpp eichangeslider.ui
            eichangebasemenuwidget.h eichangebasemenuwidget.cpp
            eichangebasemenu.h eichangebasemenu.cpp
            eichangecheckmenuwidget.h eichangecheckmenuwidget.cpp
            eichangelineedit.h eichangelineedit.cpp
            eichangedoubleslider.h eichangedoubleslider.cpp eichangedoubleslider.ui
            eichangescope.h eichangescope.cpp eichangescope.ui
            eichangeattribute.h eichangeattribute.cpp
            eichangeinputmenuwidget.h eichangeinputmenuwidget.cpp

            eichangewidgetaction.h eichangewidgetaction.cpp
            eichangeprotocolfileview.h eichangeprotocolfileview.cpp
            eichangeviewlayoutflieview.h eichangeviewlayoutflieview.cpp
            eichangeitemmodel.h eichangeitemmodel.cpp













        )
    endif()
endif()

target_link_libraries(EIChange PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(EIChange PRIVATE Qt${QT_VERSION_MAJOR}::SerialPort)
target_link_libraries(EIChange PRIVATE Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EIChange)
endif()
set_target_properties(EIChange PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS EIChange
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EIChange)
endif()
