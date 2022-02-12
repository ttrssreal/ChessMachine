#pragma once

#include "chessboard.h"

struct BoardState* util_loadfen(std::string fen, struct BoardState* board);
void util_boardstate_setpiece(struct BoardState* bs, int file, int rank, int piece);
char* util_getpiecesym(uint8_t piece);
int util_randint(int min, int max);
