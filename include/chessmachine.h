#pragma once

#include "chessboard.h"
#include "move.h"
#include <vector>

#define DEFAULTDEPTH 3

class ChessBoard;

class ChessMachine {
  private:
    std::string m_prefix = "AI";

  public:
    // pawn, knight, bishop, rook, queen
    std::vector<int> piecevalues = {1, 3, 3, 5, 9};
    struct Move m_bestmove;
    int m_depth = 3;

    std::vector<struct Move> validmoves;
    void makemove(ChessBoard* chessboard);
    void generatemoves(struct BoardState* board);

    int minimax(struct BoardState* board, int depth, int maximizingplayer);
    int evaluate(struct BoardState* board);

    void bigbrain(struct BoardState* board);
    void bigbrain(struct BoardState* board, int depth);
    void bigbrainturn(struct BoardState* board, int turn);
    void bigbrain(struct BoardState* board, int depth, int turn);

    void getpawnmoves(struct BoardState* board, uint8_t piecesquare);
    void getknightmoves(struct BoardState* board, uint8_t piecesquare);
    void getbishopmoves(struct BoardState* board, uint8_t piecesquare);
    void getrookmoves(struct BoardState* board, uint8_t piecesquare);
    void getqueenmoves(struct BoardState* board, uint8_t piecesquare);
    void getkingmoves(struct BoardState* board, uint8_t piecesquare);

    void getslidingmoves(struct BoardState* board, uint8_t piecesquare, std::vector<int> diroffs, int range);
};

// helpers
void aimovep(struct BoardState* board, Move move);
void aiundomovep(struct BoardState* board, Move move);