#include "cli.h"
#include "chessboard.h"
#include "piece.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

ChessBoard* CLI::m_targetboard;

void CLI::start(ChessBoard* chessboard) {
    CLI::m_targetboard = chessboard;

    std::string input;
    while ((input = prompt()) != "quit") {
        std::vector<std::string> args;
        int argcount = 0;

        std::string argbuff;
        for (int i = 0; i < input.length() + 1; i++) {
            if (input[i] == 0x20 || i == input.length()) { // space or end of string
                args.push_back(argbuff);
                argcount++;
                argbuff.clear();
            } else
                argbuff.push_back(input[i]);
        }

        // printboard
        if (args[0] == "p" ||
            args[0] == "print" ||
            args[0] == "printboard") {
            CLI::m_targetboard->printboard();
        }

        if (args[0] == "h" ||
            args[0] == "help") {
            CLI::printhelp();
        }

        // dodgy
        if (args[0] == "depth") {
            // only single digit
            m_targetboard->m_ai->m_depth = args[1][0] - '0';
        }

        // movepiece
        if (args[0] == "m" ||
            args[0] == "mv" ||
            args[0] == "move" ||
            args[0] == "movepiece") {
            if (argcount < 3) {
                CLI::error("Usage: eg \"movepiece e2 e4\"");
                goto ERROR;
            }
            for (int i = 1; i < args.size(); i++) {
                if (square.find(args[i]) == square.end()) {
                    std::stringstream errorstream;
                    errorstream << "\"" << args[i] << "\" is an invalid square.";
                    CLI::error(errorstream.str());
                    goto ERROR;
                }
            }
            CLI::m_targetboard->movepiece(
                {square[args[1]],
                 square[args[2]]});

            // auto make move after human

            // speeed
            auto start = std::chrono::system_clock::now();

            m_targetboard->m_ai->bigbrain(m_targetboard->m_board);

            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            std::cout << "Machine thought for " << elapsed.count() << "s" << '\n';

            m_targetboard->movepiece(m_targetboard->m_ai->m_bestmove);
        }

        // loadfen - non functioning
        if (args[0] == "l" ||
            args[0] == "load" ||
            args[0] == "loadfen") {
            if (argcount < 2)
                goto ERROR;
            // mabey use boost regex to verify in future
            CLI::m_targetboard->loadFen(args[1]);
        }

    ERROR:;
    }
}

std::string CLI::prompt() {
    std::string input;
    std::cout << "\033[38;2;255;58;243mEnter command -> \033[0m";
    getline(std::cin, input, '\n');
    return input;
}

void CLI::error(std::string msg) {
    std::cout << "\033[38;2;255;43;57m"
              << "[ERROR]: "
              << "\033[0m" << msg << "\n";
}

void CLI::error(std::string prefix, std::string msg) {
    std::cout << "\033[38;2;255;43;57m"
              << "[ERROR] ["
              << prefix
              << "]: "
              << "\033[0m" << msg << "\n";
}

void CLI::info(std::string msg) {
    std::cout << "\033[38;2;29;128;255m"
              << "[INFO]: "
              << "\033[0m" << msg << "\n";
}

void CLI::info(std::string prefix, std::string msg) {
    std::cout << "\033[38;2;29;128;255m"
              << "[INFO] ["
              << prefix
              << "]: "
              << "\033[0m" << msg << "\n";
}

void CLI::printhelp() {
    std::cout << "Commands:\n"
                 "help - Prints this... what else? commands: h, help                                                |\n"
                 "printboard - Prints the current loaded chessboard to the console. aliases: p, print, printboard   |\n"
                 "movepiece - Moves a piece between two squares. aliases: m, mv, move, movepiece                    | example: \"movepiece e2 24\"\n"
                 "depth - Sets how far the machine will look ahead. (default 3). Can only use single digits rn      | example: \"depth 5\"\n"
                 "loadfen - Loads a 'fen' complient string. aliases: l, load, loadfen                               | in progress\n";
}