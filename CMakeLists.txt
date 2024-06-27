cmake_minimum_required(VERSION 3.27)
project(PJCPROJ)

set(CMAKE_CXX_STANDARD 20)

#======================================================

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_MakeAvailable(fmt)

#======================================================

set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

#======================================================

add_executable(${PROJECT_NAME} main.cpp
        Generator.h
        Generator.cpp
        Space.cpp
        Space.h
        MainMenu.cpp
        MainMenu.h
        PostGameScreen.cpp
        PostGameScreen.h
        GamePlayInfo.cpp
        GamePlayInfo.h
        GamePlay.cpp
        GamePlay.h
        SettingsMenu.cpp
        SettingsMenu.h
)

target_link_libraries(${PROJECT_NAME} fmt)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
