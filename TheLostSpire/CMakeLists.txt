cmake_minimum_required(VERSION 3.20)
project(TheLostSpire VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Audio 비활성화 — FLAC 빌드 오류 우회
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0)
FetchContent_MakeAvailable(SFML)

add_executable(TheLostSpire
    main.cpp
    Game.cpp
    MenuState.cpp
    StateMachine.cpp
)

target_include_directories(TheLostSpire PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(TheLostSpire PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)