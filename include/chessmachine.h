#pragma once

#include "chessboard.h"
#include "move.h"
#include <vector>

class ChessBoard;

class ChessMachine {
  private:
    std::string m_prefix = "AI";

  public:
    std::vector<struct Move> validmoves;
    void makemove(ChessBoard* chessboard);
    void generatemoves(struct BoardState* board);

    void getpawnmoves(struct BoardState* board, uint8_t piecesquare);
    void getknightmoves(struct BoardState* board, uint8_t piecesquare);
    void getbishopmoves(struct BoardState* board, uint8_t piecesquare);
    void getrookmoves(struct BoardState* board, uint8_t piecesquare);
    void getqueenmoves(struct BoardState* board, uint8_t piecesquare);
    void getkingmoves(struct BoardState* board, uint8_t piecesquare);

    void getslidingmoves(struct BoardState* board, uint8_t piecesquare, std::vector<int> diroffs, int range);
};
