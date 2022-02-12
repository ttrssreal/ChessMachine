cmake_minimum_required(VERSION 3.22)
project(chessmachine VERSION 0.1 DESCRIPTION "Chess.")

set(SRC
	src/chessmachine.cpp
	src/core/chessmachine/move.cpp
	src/core/game/board/chessboard.cpp
	src/core/cli/cli.cpp
	src/gui/window.cpp
	src/gui/guichessboard.cpp
	src/util/gameutil.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_link_libraries(chessmachine SDL2main SDL2)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)