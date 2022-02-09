#pragma once

#include <string>
#include <vector>

#include "move.h"
#include "piece.h"

#define DEFAULTBOARDPOSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

struct BoardState {
    uint8_t pieces[128];
    int turn;
    uint8_t castlerights, enpassantsquare, halfmoves, fullmoves;
};

class ChessBoard {
  public:
    ChessBoard();
    ChessBoard(std::string fen);
    ~ChessBoard();

    BoardState* m_board;

    int getpiece(int x, int y);
    int pieceispresent(int x, int y);

    void loadFen(std::string fen);

    void movepiece(Move move);
    void printboard();
};

void printboarder();