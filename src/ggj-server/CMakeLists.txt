# cmake_minimum_required(VERSION 3.23)
project(ggj-server VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 20)

if(LINUX)
    file(COPY ${CMAKE_SOURCE_DIR}/content/ggj-server/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(ggj-server main.cpp)
    target_link_libraries(ggj-server galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d GameNetworkingSockets::shared)
elseif(WINDOWS)
    # Copies game content to the executable folder when CMake file is loaded.
    file(COPY ${CMAKE_SOURCE_DIR}/content/ggj-server/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(ggj-server main.cpp ${CMAKE_SOURCE_DIR}/content/logo/icon.rc
            ServerApplication.hpp
            ServerWindow.hpp
            style_cyber_mod.h
            ClientWindow.hpp
            ApplicationState.h)
    target_link_libraries(ggj-server galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d GameNetworkingSockets::shared)
    # target_link_options(ggj-server PRIVATE -mwindows)
else()
    # Not supported :)
endif()