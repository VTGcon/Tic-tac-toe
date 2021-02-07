#include <ncurses.h>
#include <string>
#include "view.h"
namespace tictactoe {
View::View(Game &game) : game_(game) {
    initscr();
    keypad(stdscr, true);
    move(0, 0);
    noecho();
}
namespace {
int &cursor_x() {
    static int x = 0;
    return x;
}
int &cursor_y() {
    static int y = 0;
    return y;
}
}  // namespace

void change(int input) {
    if (input == 'x') {
        endwin();
        exit(0);
    }
    if (input == KEY_LEFT) {
        if (cursor_y() != 0) {
            move(cursor_x(), cursor_y() - 1);
            cursor_y()--;
        }
    } else {
        if (input == KEY_RIGHT) {
            if (cursor_y() != tictactoe::Game::HEIGHT - 1) {
                move(cursor_x(), cursor_y() + 1);
                cursor_y()++;
            }
        } else {
            if (input == KEY_UP) {
                if (cursor_x() != 0) {
                    move(cursor_x() - 1, cursor_y());
                    cursor_x()--;
                }
            } else {
                if (input == KEY_DOWN) {
                    if (cursor_x() != tictactoe::Game::WIDTH - 1) {
                        move(cursor_x() + 1, cursor_y());
                        cursor_x()++;
                    }
                }
            }
        }
    }
}

bool View::read_turn() {
    int input = 0;
    move(cursor_x(), cursor_y());
    while (input != '\n' ||
           game_.bad_turn(std::make_pair(cursor_x(), cursor_y()))) {
        input = getch();
        change(input);
    }
    game_.turn(std::make_pair(cursor_x(), cursor_y()));
    return true;
}

void View::draw_result() const {
    int result = game_.is_ended();
    if (result > 0) {
        if (result == 2) {
            if (game_.get_player()) {
                addstr("O wins!\n");
            } else {
                addstr("X wins!\n");
            }
        } else {
            addstr("Draw.\n");
        }
        getch();
        endwin();
        exit(0);
    } else {
        if (game_.get_player()) {
            addstr("X move: ");
        } else {
            addstr("O move: ");
        }
    }
    refresh();
}

void View::draw_board() const {
    clear();
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            addch(game_.get_value(std::make_pair(i, j)));
        }
        addch('\n');
    }
    refresh();
    if (game_.is_ended() == 0) {
        endwin();
    }
}
}  // namespace tictactoe
