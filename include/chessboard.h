#pragma once

#include <string>

#include "chessmachine.h"
#include "move.h"

#define DEFAULTBOARDPOSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

struct BoardState {
    uint8_t pieces[128];
    int turn;
    uint8_t castlerights, enpassantsquare, halfmoves, fullmoves;
};

class ChessBoard {
  private:
    std::string m_prefix = "Chessboard";

  public:
    ChessBoard();
    ChessBoard(std::string fen);
    ~ChessBoard();

    std::string m_fen;
    struct BoardState* m_board;
    ChessMachine* m_ai;

    int getpiece(int x, int y);
    int pieceispresent(int x, int y);

    void loadFen(std::string fen);
    struct BoardState* clone();

    void movepiece(struct Move move);
    void printboard();
};