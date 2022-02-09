#include "chessboard.h"
#include "move.h"

int main() {
    ChessBoard chess;
    chess.printboard();
    chess.movepiece({
        square["b1"], // move from here
        square["c3"], // to here
    });
    chess.printboard();
    chess.movepiece({
        square["e7"],
        square["e5"],
    });
    chess.printboard();
    chess.movepiece({
        square["e2"],
        square["e4"],
    });
    chess.printboard();

    chess.loadFen("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq — 1 2");
    chess.printboard();
}