#include "game.h"
#include <view.h>
#include <algorithm>

namespace tictactoe {
Game::Game() {
    field.resize(HEIGHT, std::vector<Cell>(WIDTH, none));
}

bool Game::bad_turn(std::pair<int, int> a) const {
    return !(a.first < WIDTH && a.first >= 0) ||
           !(a.second < HEIGHT && a.second >= 0) || get_value(a) != none;
}

int Game::to_int(Cell a) {
    if (a == first_player) {
        return -1;
    }
    if (a == second_player) {
        return 1;
    }
    return 0;
}

bool Game::is_victory() const {
    for (int i = 0; i <= HEIGHT - ROW_TO_WIN; i++) {
        for (int j = 0; j <= WIDTH - ROW_TO_WIN; j++) {
            std::vector<int> sum(6, 0);
            for (int k = 0; k < ROW_TO_WIN; k++) {
                sum[0] += to_int(field[i + k][j]);
                sum[1] += to_int(field[i][j + k]);
                sum[2] += to_int(field[i + k][j + k]);
                sum[3] += to_int(field[i + k][j + ROW_TO_WIN - k - 1]);
                sum[4] +=
                    to_int(field[i + ROW_TO_WIN - 1][j + ROW_TO_WIN - 1 - k]);
                sum[5] +=
                    to_int(field[i + ROW_TO_WIN - 1 - k][j + ROW_TO_WIN - 1]);
            }
            if (std::any_of(sum.begin(), sum.end(), [](int z) {
                    return z == ROW_TO_WIN || z == -ROW_TO_WIN;
                })) {
                return true;
            }
        }
    }
    return false;
}

Game::Cell Game::get_value(std::pair<int, int> a) const {
    return field[a.first][a.second];
}

bool Game::get_player() const {
    return cur_player;
}

int Game::is_ended() const {
    if (num_of_turns == WIDTH * HEIGHT) {
        return 1;
    }
    if (is_victory()) {
        return 2;
    }
    return 0;
}

void Game::turn(std::pair<int, int> a) {
    num_of_turns++;
    if (!cur_player) {
        field[a.first][a.second] = first_player;
    } else {
        field[a.first][a.second] = second_player;
    }
    cur_player = !cur_player;
}

void play() {
    Game cur_game;
    View cur_view(cur_game);
    cur_view.draw_board();
    cur_view.draw_result();
    while (cur_game.is_ended() == 0) {
        if (cur_view.read_turn()) {
            cur_view.draw_board();
        }
        cur_view.draw_result();
    }
}
// Externally visible declarations and definitions.
}  // namespace tictactoe
