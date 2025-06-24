cmake_minimum_required(VERSION 3.29)
project(ProgrammingProjectFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProgrammingProjectFinal game_engine.cpp
        game_ui.cpp
        src/Question.cpp
        include/Question.h
        include/GameSession.h
        src/GameSession.cpp
        include/Player.h
        src/Player.cpp
)
