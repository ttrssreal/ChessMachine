#pragma once

#define WHITE 0b00000001
#define BLACK 0b00000010

#define PAWN 0b00000100
#define KNIGHT 0b00001000
#define BISHOP 0b00010000
#define ROOK 0b00100000
#define QUEEN 0b01000000
#define KING 0b10000000

#define BLANK 0b00000000

#define WHITESTRING "w"
#define BLACKSTRING "b"

#define WHITEPAWNSTRING "P"
#define WHITEKNIGHTSTRING "N"
#define WHITEBISHOPSTRING "B"
#define WHITEROOKSTRING "R"
#define WHITEQUEENSTRING "Q"
#define WHITEKINGSTRING "K"

#define BLACKPAWNSTRING "p"
#define BLACKKNIGHTSTRING "n"
#define BLACKBISHOPSTRING "b"
#define BLACKROOKSTRING "r"
#define BLACKQUEENSTRING "q"
#define BLACKKINGSTRING "k"

#include <string>
#include <unordered_map>

static std::unordered_map<std::string, uint8_t> square = { // hash map for parsing algebraic notation
    {"a1", 0x00},
    {"a2", 0x10},
    {"a3", 0x20},
    {"a4", 0x30},
    {"a5", 0x40},
    {"a6", 0x50},
    {"a7", 0x60},
    {"a8", 0x70},

    {"b1", 0x01},
    {"b2", 0x11},
    {"b3", 0x21},
    {"b4", 0x31},
    {"b5", 0x41},
    {"b6", 0x51},
    {"b7", 0x61},
    {"b8", 0x71},

    {"c1", 0x02},
    {"c2", 0x12},
    {"c3", 0x22},
    {"c4", 0x32},
    {"c5", 0x42},
    {"c6", 0x52},
    {"c7", 0x62},
    {"c8", 0x72},

    {"d1", 0x03},
    {"d2", 0x13},
    {"d3", 0x23},
    {"d4", 0x33},
    {"d5", 0x43},
    {"d6", 0x53},
    {"d7", 0x63},
    {"d8", 0x73},

    {"e1", 0x04},
    {"e2", 0x14},
    {"e3", 0x24},
    {"e4", 0x34},
    {"e5", 0x44},
    {"e6", 0x54},
    {"e7", 0x64},
    {"e8", 0x74},

    {"f1", 0x05},
    {"f2", 0x15},
    {"f3", 0x25},
    {"f4", 0x35},
    {"f5", 0x45},
    {"f6", 0x55},
    {"f7", 0x65},
    {"f8", 0x75},

    {"g1", 0x06},
    {"g2", 0x16},
    {"g3", 0x26},
    {"g4", 0x36},
    {"g5", 0x46},
    {"g6", 0x56},
    {"g7", 0x66},
    {"g8", 0x76},

    {"h1", 0x07},
    {"h2", 0x17},
    {"h3", 0x27},
    {"h4", 0x37},
    {"h5", 0x47},
    {"h6", 0x57},
    {"h7", 0x67},
    {"h8", 0x77}};
