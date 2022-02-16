#include "chessboard.h"
#include "chessmachine.h"
#include "gameutil.h"
#include "move.h"
#include <iostream>

// this took longer than it should :)
// not yet optimized
int ChessMachine::minimax(struct BoardState* board, int depth, int iswhite) {
    int maxeval, mineval, curreval;
    if (depth == 0)                                   // on a tree leaf
        return evaluate(board);                       // pass the evaluation to your parent
    if (iswhite) {                                    // from whos perspective
        maxeval = INT32_MIN;                          // no eval is lower
        generatemoves(board);                         // member "validmoves" has the moves
        std::vector<struct Move> vmoves = validmoves; // store them on the stack
        for (int i = 0; i < vmoves.size(); i++) {     // what moves can white play
            // make sure to save the piece you took or when capturing you loose the piece forever :|
            uint8_t capturedpiece = board->pieces[vmoves[i].moveto];
            aimovep(board, vmoves[i]);                   // make your move
            curreval = minimax(board, depth - 1, false); // recurse into all blacks responses and get the eval for them
            // undo your move && reset the captured piece, to not mess up the boardstate for the next iteration
            aiundomovep(board, vmoves[i]);
            board->pieces[vmoves[i].moveto] = capturedpiece;
            // if we have a new best eval then save it
            if (curreval >= maxeval) {
                maxeval = curreval;
                // if we are layer 0 of the tree then set the move as the most preferable
                if (depth == m_depth)
                    m_bestmove = vmoves[i];
            }
        }
        // give the best moves evaluation to you parent node
        return maxeval;
    } else if (!iswhite) {
        mineval = INT32_MAX;
        generatemoves(board);
        std::vector<struct Move> vmoves = validmoves;
        for (int i = 0; i < vmoves.size(); i++) {
            uint8_t capturedpiece = board->pieces[vmoves[i].moveto];
            aimovep(board, vmoves[i]);
            curreval = minimax(board, depth - 1, true);
            aiundomovep(board, vmoves[i]);
            board->pieces[vmoves[i].moveto] = capturedpiece;
            if (curreval <= mineval) {
                mineval = curreval;
                if (depth == m_depth)
                    m_bestmove = vmoves[i];
            }
        }
        return mineval;
    }
}

// pretty crap but can be improved
// white is +, black is -
int ChessMachine::evaluate(struct BoardState* board) {
    // just add up all the piece values with weights spec in chessmachines "piecevalues"
    int evaluation = 0;
    for (int i = 0; i < 128; i++) {
        if (i % 16 < 8) { // inside the board
            uint8_t piece = board->pieces[i];
            if ((piece & PAWN) == PAWN) {
                ((piece & WHITE) == WHITE) ? evaluation += piecevalues[0] : evaluation -= piecevalues[0];
                continue;
            }
            if ((piece & KNIGHT) == KNIGHT) {
                ((piece & WHITE) == WHITE) ? evaluation += piecevalues[1] : evaluation -= piecevalues[1];
                continue;
            }
            if ((piece & BISHOP) == BISHOP) {
                ((piece & WHITE) == WHITE) ? evaluation += piecevalues[2] : evaluation -= piecevalues[2];
                continue;
            }
            if ((piece & ROOK) == ROOK) {
                ((piece & WHITE) == WHITE) ? evaluation += piecevalues[3] : evaluation -= piecevalues[3];
                continue;
            }
            if ((piece & QUEEN) == QUEEN) {
                ((piece & WHITE) == WHITE) ? evaluation += piecevalues[4] : evaluation -= piecevalues[4];
                continue;
            }
        }
    }
    return evaluation;
}

// wrappers

// default depth=3
void ChessMachine::bigbrain(struct BoardState* board) {
    bigbrainturn(board, board->turn);
}

void ChessMachine::bigbrainturn(struct BoardState* board, int turn) {
    bigbrain(board, m_depth, turn);
}

void ChessMachine::bigbrain(struct BoardState* board, int depth) {
    bigbrain(board, depth, board->turn);
}

// find the best move and put it in m_bestmove
void ChessMachine::bigbrain(struct BoardState* board, int depth, int turn) {
    m_depth = depth;
    minimax(board, m_depth, turn);
}

// helper functions idk

void aimovep(struct BoardState* board, Move move) {
    uint8_t piece = board->pieces[move.movefrom];
    board->pieces[move.moveto] = piece;
    board->pieces[move.movefrom] = BLANK;
    board->turn = !board->turn;
}

void aiundomovep(struct BoardState* board, Move move) {
    board->turn = !board->turn;
    uint8_t piece = board->pieces[move.moveto];
    board->pieces[move.movefrom] = piece;
    board->pieces[move.moveto] = BLANK;
}