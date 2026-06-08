cmake_minimum_required(VERSION 3.20)

project(EndlessShooter)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(EndlessShooter
    src/main.cpp
    src/Player.cpp
)

target_link_libraries(EndlessShooter
    SFML::Graphics
    SFML::Window
    SFML::System
)