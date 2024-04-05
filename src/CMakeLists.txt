cmake_minimum_required(VERSION 3.0)

project(SmartCalc_v2 VERSION 0.1 LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(icon)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT5_DIR}/lib/cmake")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        resources/resources.qrc
        resources/icons/icon.ico
        resources/icons/graph.ico
        resources/icons/icon.icns
        resources/style_main_window/background_one.jpeg
        resources/style_main_window/background_two.jpg
        main.cc

        view/mainwindow.cpp
        view/mainwindow.h
        view/mainwindow.ui
        view/smartcalc.h view/smartcalc.cpp view/smartcalc.ui
        view/QCustomPlot/qcustomplot.cc
        view/QCustomPlot/qcustomplot.h
        view/credit_calc.h
        view/credit_calc.cpp
        view/credit_calc.ui
        model/calculate.cc
        model/check_sequence.cc
        model/conversion.cc
        model/lexem.cc
        model/validation.cc
        model/parser.cc
        model/lexem.h
        model/parser.h
        model/validation.h
        model/conversion.h
        model/calculate.h
        model/check_sequence.h
        model/credit.h
        model/credit.cc
        controller/controller_smart_calc.h
        controller/controller_credit_calc.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc21
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalc21 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Tcalc21 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalc21
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalc21 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SmartCalc21 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set_source_files_properties(resources/icons/icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc21)
endif()


add_compile_options("-Wall -Wextra -Wpedantic -Werror -g")
