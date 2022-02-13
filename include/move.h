#pragma once

#include "piece.h"
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>

struct Move {
    uint8_t movefrom;
    uint8_t moveto;
    void print() {
        std::cout << squarerev[(int)movefrom] << ", " << squarerev[(int)moveto] << "\n";
    }
    std::string getstring() {
        std::stringstream ss;
        ss << squarerev[(int)movefrom] << ", " << squarerev[(int)moveto];
        return ss.str();
    }
};