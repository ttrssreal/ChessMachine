#pragma once

#include "piece.h"
#include <iostream>
#include <stdint.h>

struct Move {
    uint8_t movefrom;
    uint8_t moveto;
    void print() {
        std::cout << squarerev[(int)movefrom] << ", " << squarerev[(int)moveto] << "\n";
    }
};