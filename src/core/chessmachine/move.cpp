#include "move.h"
#include "chessboard.h"
#include "chessmachine.h"
#include "cli.h"
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
            if ((piece & PAWN) == PAWN) {
                getpawnmoves(board, i);
            }
            if ((piece & KNIGHT) == KNIGHT) {
                getknightmoves(board, i);
            }
            if ((piece & BISHOP) == BISHOP) {
                getbishopmoves(board, i);
            }
            if ((piece & ROOK) == ROOK) {
                getrookmoves(board, i);
            }
            if ((piece & QUEEN) == QUEEN) {
                getqueenmoves(board, i);
            }
            if ((piece & KING) == KING) {
                getkingmoves(board, i);
            }
        }
    }
}

void ChessMachine::getpawnmoves(struct BoardState* board, uint8_t piecesquare) {
    if (board->turn == WHITE) {                              // is it whites turn?
        if (((board->pieces[piecesquare] & WHITE) != WHITE)) // is the piece white?
            return;
        // moves
        if (board->pieces[piecesquare + 0x10] == BLANK) {                         // is the square in front empty
            validmoves.push_back((struct Move){piecesquare, piecesquare + 0x10}); // yes? add it
            // is the square in fron of that on empty. and is the pawn on the 2nd rank?
            // mask 11110000 gives the rank, >> 4 divides it by 0x10
            if (board->pieces[piecesquare + 0x20] == BLANK && ((piecesquare & 0b11110000) >> 4) == 1)
                // yes? then add it
                validmoves.push_back((struct Move){piecesquare, piecesquare + 0x20});
        }
        // captures
        if ((board->pieces[piecesquare + 0x11] & BLACK) == BLACK) {
            validmoves.push_back((struct Move){piecesquare, piecesquare + 0x11});
        }
        if ((board->pieces[piecesquare + 0xf] & BLACK) == BLACK) {
            validmoves.push_back((struct Move){piecesquare, piecesquare + 0xf});
        }
    } else if (board->turn == 0) {
        if (((board->pieces[piecesquare] & BLACK) != BLACK))
            return;
        if (board->pieces[piecesquare - 0x10] == BLANK) {
            validmoves.push_back((struct Move){piecesquare, piecesquare - 0x10});
            if (board->pieces[piecesquare - 0x20] == BLANK && ((piecesquare & 0b11110000) >> 4) == 6)
                validmoves.push_back((struct Move){piecesquare, piecesquare - 0x20});
        }
        if ((board->pieces[piecesquare - 0x11] & WHITE) == WHITE) {
            validmoves.push_back((struct Move){piecesquare, piecesquare - 0x11});
        }
        if ((board->pieces[piecesquare - 0xf] & WHITE) == WHITE) {
            validmoves.push_back((struct Move){piecesquare, piecesquare - 0xf});
        }
    }
}

void ChessMachine::getknightmoves(struct BoardState* board, uint8_t piecesquare) {
    // relative square offsets in 0x88 for a knight
    std::vector<int> relsqroff = {
        0x21, 0x1f, 0xe, 0x12,
        -0x21, -0x1f, -0xe, -0x12};

    for (int i = 0; i < relsqroff.size(); i++) {
        int targetsquare = piecesquare + relsqroff[i];
        if ((targetsquare & 0x88) != 0) // square is on the board
            continue;
        if (board->turn == 1 && ((board->pieces[piecesquare] & WHITE) == WHITE)) {
            if (board->pieces[targetsquare] == BLANK) {
                validmoves.push_back((struct Move){piecesquare, targetsquare});
                continue;
            }
            if ((board->pieces[targetsquare] & BLACK) == BLACK) {
                validmoves.push_back((struct Move){piecesquare, targetsquare});
            }
        }
        if (board->turn == 0 && ((board->pieces[piecesquare] & BLACK) == BLACK)) {
            if (board->pieces[targetsquare] == BLANK) {
                validmoves.push_back((struct Move){piecesquare, targetsquare});
                continue;
            }
            if ((board->pieces[targetsquare] & WHITE) == WHITE) {
                validmoves.push_back((struct Move){piecesquare, targetsquare});
            }
        }
    }
}

void ChessMachine::getbishopmoves(struct BoardState* board, uint8_t piecesquare) {
    getslidingmoves(board, piecesquare, {0x11, 0xf, -0x11, -0xf}, 0);
}

void ChessMachine::getrookmoves(struct BoardState* board, uint8_t piecesquare) {
    getslidingmoves(board, piecesquare, {0x10, 0x1, -0x10, -0x1}, 0);
}

void ChessMachine::getqueenmoves(struct BoardState* board, uint8_t piecesquare) {
    getslidingmoves(board, piecesquare, {0x10, 0x1, -0x10, -0x1, 0x11, 0xf, -0x11, -0xf}, 0);
}

void ChessMachine::getkingmoves(struct BoardState* board, uint8_t piecesquare) {
    getslidingmoves(board, piecesquare, {0x10, 0x1, -0x10, -0x1, 0x11, 0xf, -0x11, -0xf}, 1);
}

// range = 0, for infinite
// direction offsets are a list of +1 in the direction (0x88) eg. up and left is 0xf
void ChessMachine::getslidingmoves(struct BoardState* board, uint8_t piecesquare, std::vector<int> diroffs, int range) {
    for (int i = 0; i < diroffs.size(); i++) {
        if (board->turn == 1 && ((board->pieces[piecesquare] & WHITE) == WHITE)) {
            int offset = diroffs[i];
            for (; (((piecesquare + offset) & 0x88) == 0) &&           // target is on-board
                   (board->pieces[piecesquare + offset] == BLANK);     // target is empty
                 offset += diroffs[i]) {                               // next square in that direction
                if ((range != 0) && ((offset / diroffs[i]) > range)) { // how far have gone?
                    break;
                }
                validmoves.push_back((struct Move){piecesquare, piecesquare + offset});
            }
            if ((board->pieces[piecesquare + offset] & BLACK) == BLACK) { // take if square is black
                if (((piecesquare + offset) & 0x88) == 0) {               // capture is on board?
                    validmoves.push_back((struct Move){piecesquare, piecesquare + offset});
                }
            }
        }
        if (board->turn == 0 && ((board->pieces[piecesquare] & BLACK) == BLACK)) {
            int offset = diroffs[i];
            for (; (((piecesquare + offset) & 0x88) == 0) &&
                   (board->pieces[piecesquare + offset] == BLANK);
                 offset += diroffs[i]) {
                if ((range != 0) && ((offset / diroffs[i]) > range)) {
                    break;
                }
                validmoves.push_back((struct Move){piecesquare, piecesquare + offset});
            }
            if ((board->pieces[piecesquare + offset] & WHITE) == WHITE) { // take if square is white
                if (((piecesquare + offset) & 0x88) == 0) {
                    validmoves.push_back((struct Move){piecesquare, piecesquare + offset});
                }
            }
        }
    }
}

void ChessMachine::makemove(ChessBoard* chessboard) {
    if (validmoves.size() <= 0) {
        CLI::info(m_prefix, "No moves... ig u beat me :(");
        return;
    }
    int rand = util_randint(0, validmoves.size() - 1);
    struct Move chosen_move = validmoves[rand];
    chessboard->movepiece(chosen_move);
}