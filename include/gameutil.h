#pragma once

#include "chessboard.h"

BoardState* util_loadfen(std::string fen, BoardState* board);
void util_boardstate_setpiece(BoardState* bs, int file, int rank, int piece);