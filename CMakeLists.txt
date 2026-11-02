cmake_minimum_required(VERSION 3.19)
project(octapedal LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Multimedia)
find_package(Sndfile REQUIRED)


set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

qt_add_executable(octapedal
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    customdial.h customdial.cpp
    ui/controls/RotaryKnob.h    ui/controls/RotaryKnob.cpp
    ui/controls/Manager.h ui/controls/Manager.cpp
    images.qrc
    cmake/modules/FindSndfile.cmake
    audio.h audio.cpp
    audiorunnable.h audiorunnable.cpp
)

qt_add_translations(
    TARGETS octapedal
    TS_FILES octapedal_en_US.ts
)

target_link_libraries(octapedal
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        sndfile
)

install(TARGETS octapedal
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET octapedal
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
