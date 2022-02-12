#include "gameutil.h"

#include <sstream>
#include <string>

#include "chessboard.h"
#include "piece.h"

// default
// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

struct BoardState* util_loadfen(std::string fen, struct BoardState* board) {
    std::stringstream fenstream(fen);
    std::string fensectionbuff, fensectionstring;
    std::vector<std::string> fensections;
    while (std::getline(fenstream, fensectionbuff, ' ')) {
        fensections.push_back(fensectionbuff);
    }

    // board/piece setup
    fensectionstring = fensections.at(0);
    int pointerfile = 0;
    int pointerrank = 7;
    for (int i = 0; i < fensectionstring.length(); i++) {
        char letter = fensectionstring[i];

        if (letter > 48 && letter < 57) {
            // for number chars ie. iterating over whitespace
            for (int j = 0; j < (letter - 48); j++) {
                util_boardstate_setpiece(board, pointerfile, pointerrank, BLANK);
                pointerfile++;
            }
        } else if (letter == '/') {
            pointerrank--;
            pointerfile = 0;
        } else {
            int piece;
            switch (letter) {
            case 'P':
                piece = WHITE | PAWN;
                break;
            case 'N':
                piece = WHITE | KNIGHT;
                break;
            case 'B':
                piece = WHITE | BISHOP;
                break;
            case 'R':
                piece = WHITE | ROOK;
                break;
            case 'Q':
                piece = WHITE | QUEEN;
                break;
            case 'K':
                piece = WHITE | KING;
                break;

            case 'p':
                piece = BLACK | PAWN;
                break;
            case 'n':
                piece = BLACK | KNIGHT;
                break;
            case 'b':
                piece = BLACK | BISHOP;
                break;
            case 'r':
                piece = BLACK | ROOK;
                break;
            case 'q':
                piece = BLACK | QUEEN;
                break;
            case 'k':
                piece = BLACK | KING;
                break;

            default:
                break;
            }
            util_boardstate_setpiece(board, pointerfile, pointerrank, piece);
            pointerfile++;
        }
    }

    // other state info

    // turn
    board->turn = fensections.at(1) == WHITESTRING ? 1 : 0;

    // castling rights
    fensectionstring = fensections.at(2);
    board->castlerights = 0b0000;
    for (int i = 0; i < fensectionstring.length(); i++) {
        char letter = fensectionstring[i];
        switch (letter) {
        case 'K':
            board->castlerights |= 0b1000;
            break;
        case 'Q':
            board->castlerights |= 0b0100;
            break;
        case 'k':
            board->castlerights |= 0b0010;
            break;
        case 'q':
            board->castlerights |= 0b0001;
            break;

        default:
            break;
        }
    }

    return board;
}

void util_boardstate_setpiece(struct BoardState* board, int file, int rank, int piece) {
    board->pieces[(rank << 4) + file] = piece;
    return;
}

// get piece symbol ie. p B q r N
char* util_getpiecesym(uint8_t piece) {
    switch (piece) {
    case (WHITE | PAWN):
        return WHITEPAWNSTRING;
        break;
    case (WHITE | KNIGHT):
        return WHITEKNIGHTSTRING;
        break;
    case (WHITE | BISHOP):
        return WHITEBISHOPSTRING;
        break;
    case (WHITE | ROOK):
        return WHITEROOKSTRING;
        break;
    case (WHITE | QUEEN):
        return WHITEQUEENSTRING;
        break;
    case (WHITE | KING):
        return WHITEKINGSTRING;
        break;

    case (BLACK | PAWN):
        return BLACKPAWNSTRING;
        break;
    case (BLACK | KNIGHT):
        return BLACKKNIGHTSTRING;
        break;
    case (BLACK | BISHOP):
        return BLACKBISHOPSTRING;
        break;
    case (BLACK | ROOK):
        return BLACKROOKSTRING;
        break;
    case (BLACK | QUEEN):
        return BLACKQUEENSTRING;
        break;
    case (BLACK | KING):
        return BLACKKINGSTRING;
        break;
    default:
        return "-"; // blank square symbol
        break;
    }
}

// stack overflow lamo
int util_randint(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}
