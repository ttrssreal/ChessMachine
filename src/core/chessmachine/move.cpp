#include "move.h"
#include "chessboard.h"
#include "chessmachine.h"
#include "gameutil.h"
#include "piece.h"
#include <bitset>
#include <iostream>
#include <vector>

// 0x88 off-board detection: On board if, square & 0x88 == 0

void ChessMachine::generatemoves(struct BoardState* board) {
    validmoves.clear();
    for (int i = 0; i < 128; i++) {
        if (i % 16 < 8) { // inside the board
            struct Move move;
            uint8_t piece = board->pieces[i];
            if ((piece & (1 << 2)) == (1 << 2)) {
                getpawnmoves(board, i);
            }
        }
    }
}

void ChessMachine::getpawnmoves(struct BoardState* board, uint8_t pawnsquare) {
    if (board->turn == 1 && board->pieces[pawnsquare + 0x10] == BLANK && ((board->pieces[pawnsquare] & 1) == 1)) {
        validmoves.push_back((struct Move){pawnsquare, pawnsquare + 0x10});
    } else if (board->turn == 0 && board->pieces[pawnsquare - 0x10] == BLANK && ((board->pieces[pawnsquare] & (1 << 1)) == (1 << 1))) {
        validmoves.push_back((struct Move){pawnsquare, pawnsquare - 0x10});
    } else
        return;
}

void ChessMachine::makemove(ChessBoard* chessboard) {
    struct Move chosen_move = validmoves[util_randint(0, validmoves.size() - 1)];
    chosen_move.print();
    chessboard->movepiece(chosen_move);
}
