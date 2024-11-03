# cmake_minimum_required(VERSION 3.23)
project(galder-game-jam-2023 VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 20)

if(LINUX)
    # Copies game content to the executable folder when CMake file is loaded.
    file(COPY ${CMAKE_SOURCE_DIR}/content/game/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(galder-game-jam-2023 main.cpp)
    target_link_libraries(galder-game-jam-2023 galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
elseif(WINDOWS)
    # Copies game content to the executable folder when CMake file is loaded.
    file(COPY ${CMAKE_SOURCE_DIR}/content/game/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(galder-game-jam-2023 main.cpp ${CMAKE_SOURCE_DIR}/content/logo/icon.rc)
    target_link_libraries(galder-game-jam-2023 galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
    # target_link_options(galder-game-jam-2023 PRIVATE -mwindows)
else()
    set(MACOSX_BUNDLE_BUNDLE_NAME "GalderGameJam2023")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "galder.game.jam.2023")
    set(MACOSX_BUNDLE_INFO_STRING "GalderGameJam2023")
    set(MACOSX_BUNDLE_ICON_FILE "AppIcon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING 0.1.2)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1.2)
    set(MACOSX_BUNDLE_BUNDLE_VERSION 0.1.2)

    set(icon_file_path "${CMAKE_SOURCE_DIR}/content/logo/AppIcon.icns")
    set_source_files_properties(${icon_file_path} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    add_executable(GalderGameJam2023 MACOSX_BUNDLE main.cpp)
    target_link_libraries(GalderGameJam2023 galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
    set_target_properties(GalderGameJam2023 PROPERTIES
            MACOSX_BUNDLE TRUE)
    file(COPY ${CMAKE_SOURCE_DIR}/content/game/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/GalderGameJam2023.app/Contents/MacOS)
    file(COPY ${CMAKE_SOURCE_DIR}/content/logo/AppIcon.icns DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/GalderGameJam2023.app/Contents/Resources)
endif()