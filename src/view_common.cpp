#include <iostream>
#include "view.h"

namespace tictactoe {
void View::draw_result() const {
    int result = game_.is_ended();
    if (result > 0) {
        if (result == 2) {
            if (game_.get_player()) {
                std::cout << "O wins!" << '\n';
            } else {
                std::cout << "X wins!" << '\n';
            }
        } else {
            std::cout << "Draw." << '\n';
        }
    } else {
        if (game_.get_player()) {
            std::cout << "X move: ";
        } else {
            std::cout << "O move: ";
        }
    }
}

void View::bad_comment() {
    std::cout << "Bad move!" << '\n';
}

void View::drawing() const {
    std::cout << '\n';
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            std::cout << static_cast<char>(
                game_.get_value(std::make_pair(i, j)));
        }
        std::cout << '\n';
    }
}

bool View::read_turn() {
    std::string data;
    char symbol = 0;
    bool num1_exist = false;
    bool num2_exist = false;
    bool num3_exist = false;
    while (std::cin.get(symbol)) {
        if (symbol == '\n') {
            break;
        }
        if ((symbol < '0' || symbol > '9') && symbol != '-' && symbol != ' ') {
            std::string finish_line;
            getline(std::cin, finish_line);
            return false;
        }
        if ((symbol >= '0' && symbol <= '9') && std::cin.peek() == '-') {
            std::string finish_line;
            getline(std::cin, finish_line);
            return false;
        }
        if (symbol == '-' && std::cin.peek() == ' ') {
            std::string finish_line;
            getline(std::cin, finish_line);
            return false;
        }
        if (symbol <= '9' && symbol >= '0') {
            if (!num1_exist) {
                num1_exist = true;
            } else if (data[data.length() - 1] == ' ' ||
                       data[data.length() - 1] == '-') {
                if (!num2_exist) {
                    num2_exist = true;
                } else {
                    num3_exist = true;
                }
            }
        }
        data += symbol;
        if (num3_exist) {
            std::string finish_line;
            getline(std::cin, finish_line);
            return false;
        }
    }
    if (!num1_exist || !num2_exist) {
        return false;
    }
    int x = 0;
    int y = 0;
    size_t i = 0;
    while (data[i] == ' ') {
        i++;
    }
    int j = i;
    while (data[i] != ' ') {
        i++;
    }
    x = std::stoi(data.substr(j, i));
    while (data[i] == ' ') {
        i++;
    }
    j = i;
    while (i < data.length() && data[i] != ' ') {
        i++;
    }
    y = std::stoi(data.substr(j, i));
    std::pair<int, int> move = std::make_pair(x, y);
    if (move == std::make_pair(-1, -1)) {
        exit(0);
    }
    if (game_.bad_turn(move)) {
        bad_comment();
        return false;
    }
    game_.turn(move);
    return true;
}

}  // namespace tictactoe
