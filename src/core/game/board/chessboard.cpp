#include "chessboard.h"

#include <iostream>
#include <stdint.h>
#include <string>

#include "chessmachine.h"
#include "cli.h"
#include "gameutil.h"
#include "move.h"
#include "piece.h"
#include <assert.h>

ChessBoard::ChessBoard() : ChessBoard(DEFAULTBOARDPOSITION) {}

ChessBoard::ChessBoard(std::string fen) {
    m_board = new struct BoardState;
    m_ai = new ChessMachine;
    loadFen(fen);
}

ChessBoard::~ChessBoard() {
    delete m_board;
    delete m_ai;
}

void ChessBoard::printboard() {
    CLI::info(this->prefix, "");
    std::string line;
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            uint8_t piece = getpiece(file, rank);
            char* letter = util_getpiecesym(piece);
            std::cout << letter << " ";
        }
        std::cout << std::endl;
    }

    // turn
    std::cout << "Turn to move: ";
    if (m_board->turn)
        std::cout << "White";
    else
        std::cout << "Black";

    std::cout << std::endl;

    // castle rights
    std::cout << "Can castle: ";
    if (m_board->castlerights & 1)
        std::cout
            << "q ";
    if ((m_board->castlerights & (1 << 1)) == (1 << 1)) // second bit etc
        std::cout
            << "k ";
    if ((m_board->castlerights & (1 << 2)) == (1 << 2))
        std::cout
            << "Q ";
    if ((m_board->castlerights & (1 << 3)) == (1 << 3))
        std::cout
            << "K ";
    std::cout << std::endl;
}

int ChessBoard::getpiece(int file, int rank) {
    return m_board->pieces[(rank << 4) + file];
}

void ChessBoard::movepiece(struct Move move) {
    // no verification of correct moves... yet
    int movingpiece = m_board->pieces[move.movefrom];
    m_board->pieces[move.moveto] = movingpiece;
    m_board->pieces[move.movefrom] = BLANK;

    if (m_board->turn == 1)
        std::cout << "White made move." << std::endl;
    else if (m_board->turn == 0)
        std::cout << "Black made move." << std::endl;

    m_board->turn = !m_board->turn; // flip move
}

void ChessBoard::loadFen(std::string fen) {
    util_loadfen(fen, m_board);
    CLI::info(this->prefix, "Successfully loaded new game.");
}