# cmake_minimum_required(VERSION 3.23)
project(galder-game-experiments VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 20)

if(LINUX)
    add_executable(galder-game-experiments main.cpp)
    target_link_libraries(galder-game-experiments galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
elseif(WINDOWS)
    # Copies game content to the executable folder when CMake file is loaded.
    file(COPY ${CMAKE_SOURCE_DIR}/content/game/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(galder-game-experiments main.cpp ${CMAKE_SOURCE_DIR}/content/logo/icon.rc)
    target_link_libraries(galder-game-experiments galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
    # target_link_options(galder-game-experiments PRIVATE -mwindows)
else()
    # Not supported :)
endif()