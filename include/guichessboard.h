#pragma once
#include "chessboard.h"
#include "window.h"

class GUIChessBoard {
  private:
    static Window* m_win;

  public:
    GUIChessBoard();
    ~GUIChessBoard();

    static void start(ChessBoard* chessboard);
};