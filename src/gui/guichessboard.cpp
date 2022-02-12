#include "guichessboard.h"
#include "chessboard.h"
#include "cli.h"
#include "window.h"
#include <iostream>

#define FPS 2

Window* GUIChessBoard::m_win;

GUIChessBoard::~GUIChessBoard() {
    delete GUIChessBoard::m_win;
}

void GUIChessBoard::start(ChessBoard* chessboard) {
    GUIChessBoard::m_win = new Window(800, 800);

    // int delay = 1000 / FPS;

    // int start,
    //     ftime;
    SDL_Event ev;
    for (SDL_Event ev; ev.type != SDL_QUIT; SDL_PollEvent(&ev)) {
        // start = SDL_GetTicks();
        // std::cout << ftime;

        // update state
        GUIChessBoard::m_win->boardstate = chessboard->m_board;

        // render
        GUIChessBoard::m_win->clear();
        GUIChessBoard::m_win->drawboard();
        GUIChessBoard::m_win->render();
        // ftime = SDL_GetTicks() - start;
        // if (delay > ftime) {
        //     SDL_Delay(delay - ftime);
        // }
    }
    exit(0);
}
