cmake_minimum_required(VERSION 3.19)
project(Hamster-WheelQT LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets UiTools Svg)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui


    resource.qrc
)

qt_add_resources(SOURCES resource.qrc)

qt_add_executable(Hamster-WheelQT
    WIN32 MACOSX_BUNDLE
    ${SOURCES}


)



target_link_libraries(Hamster-WheelQT
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::UiTools
        Qt::Svg
)

include(GNUInstallDirs)

install(TARGETS Hamster-WheelQT
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Hamster-WheelQT
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
