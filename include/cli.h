#pragma once
#include "chessboard.h"
#include <string>

class CLI {
  private:
    static ChessBoard* m_targetboard;

  public:
    static void start(ChessBoard* chessboard);

    static void info(std::string prefix, std::string msg);
    static void info(std::string msg);

    static void error(std::string prefix, std::string msg);
    static void error(std::string msg);

    static std::string prompt();
};
