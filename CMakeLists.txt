cmake_minimum_required(VERSION 3.5)

project(DesktopApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(VCPKG_INCLUDE_DIR "D:/vcpkg/installed/x64-windows/include")
# set(VCPKG_LIB_DIR "D:/vcpkg/installed/x64-windows/lib")

# set(BOOST_ROOT "D:/vcpkg/installed/x64-windows/share/boost")

# set (Boost_NO_SYSTEM_PATHS ON)
# set (Boost_USE_MULTITHREADED ON)
# set (Boost_USE_STATIC_LIBS ON)
# set (Boost_USE_STATIC_RUNTIME OFF)
# set (BOOST_ALL_DYN_LINK OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# include_directories(${VCPKG_INCLUDE_DIR})
#link_directories(${VCPKG_LIB_DIR})
# if (Boost_FOUND)
#     include_directories (SYSTEM ${Boost_INCLUDE_DIR})
# endif ()


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DesktopApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        utils.h utils.cpp
        money.h money.cpp money.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DesktopApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DesktopApp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DesktopApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DesktopApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets) #${Boost_LIBRARIES} wsock32 setupapi ws2_32)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DesktopApp)
endif()
set_target_properties(DesktopApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DesktopApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DesktopApp)
endif()
