cmake_minimum_required(VERSION 3.6)
project(ASS1)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(ASS1
        include/Card.h
        include/Deck.h
        include/Game.h
        include/Hand.h
        include/Player.h
        src/Card.cpp
        src/Deck.cpp
        src/Game.cpp
        src/Hand.cpp
        src/Player.cpp
        src/reviiyot.cpp
        )
