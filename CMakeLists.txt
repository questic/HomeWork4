cmake_minimum_required(VERSION 3.26)
project(HomeWork4)

set(CMAKE_CXX_STANDARD 17)

add_executable(HomeWork4 src/main.cpp
        src/Player.cpp
        src/Player.h
        src/Utils.cpp
        src/Utils.h
        src/Enemy.cpp
        src/Enemy.h
        src/Weapon.cpp
        src/Weapon.h)
