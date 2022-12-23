cmake_minimum_required(VERSION 3.5)

project(qbrainwave VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Bluetooth)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Bluetooth)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        mindwave.cpp
        mindwave.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qBrainwaveOSC APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qBrainwaveOSC SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Bluetooth)

if(APPLE)
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER donarturo11.${PROJECT_NAME}.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    INSTALL_RPATH @executable_path/../Frameworks
)
elseif(WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)
endif()



install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

### MINGW - FILES REQUIRED TO RUN ###
if(MINGW)
    install( FILES
        $ENV{MSYSTEM_PREFIX}/bin/libbrotlicommon.dll
        $ENV{MSYSTEM_PREFIX}/bin/libbrotlidec.dll
        $ENV{MSYSTEM_PREFIX}/bin/libbz2-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libdouble-conversion.dll
        $ENV{MSYSTEM_PREFIX}bin/libfreetype-6.dll
        $ENV{MSYSTEM_PREFIX}bin/libgcc_s_seh-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libglib-2.0-0.dll
        $ENV{MSYSTEM_PREFIX}/bin/libgraphite2.dll
        $ENV{MSYSTEM_PREFIX}/bin/libharfbuzz-0.dll
        $ENV{MSYSTEM_PREFIX}/bin/libiconv-2.dll
        $ENV{MSYSTEM_PREFIX}/bin/libicudt69.dll
        $ENV{MSYSTEM_PREFIX}/bin/libicuin69.dll
        $ENV{MSYSTEM_PREFIX}/bin/libicuuc69.dll
        $ENV{MSYSTEM_PREFIX}/bin/libintl-8.dll
        $ENV{MSYSTEM_PREFIX}/bin/libmd4c.dll
        $ENV{MSYSTEM_PREFIX}/bin/libpcre-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libpcre2-16-0.dll
        $ENV{MSYSTEM_PREFIX}/bin/libpng16-16.dll
        $ENV{MSYSTEM_PREFIX}/bin/libstdc++-6.dll
        $ENV{MSYSTEM_PREFIX}/bin/libwinpthread-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libzstd.dll
        $ENV{MSYSTEM_PREFIX}/bin/zlib1.dll
    DESTINATION ${PROJECT_NAME})
    install( FILES
        $ENV{MSYSTEM_PREFIX}/bin/Qt5Core.dll
        $ENV{MSYSTEM_PREFIX}/bin/Qt5Gui.dll
        $ENV{MSYSTEM_PREFIX}/bin/Qt5Widgets.dll
        DESTINATION ${PROJECT_NAME})
    install( DIRECTORY
        $ENV{MSYSTEM_PREFIX}/share/qt5/plugins/platforms
        $ENV{MSYSTEM_PREFIX}/share/qt5/plugins/styles
        DESTINATION ${PROJECT_NAME})
endif()
### END MINGW ###

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
