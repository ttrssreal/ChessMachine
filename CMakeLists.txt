cmake_minimum_required(VERSION 3.22)
project(chessmachine VERSION 0.1 DESCRIPTION "Chess.")

set(CMAKE_BUILD_TYPE Debug) # set to Release if you want

set(SRC
	src/chessmachine.cpp
	src/core/chessmachine/move.cpp
	src/core/chessmachine/ai.cpp
	src/core/game/board/chessboard.cpp
	src/core/cli/cli.cpp
	src/util/gameutil.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)