#include "game.h"
#include <view.h>
#include "mytest.h"

namespace tictactoe {
TEST_CASE("If turn is out of field") {
    Game test_game;
    for (int i = 0; i < 10; i++) {
        CHECK(test_game.bad_turn({i, 10}) == true);
        CHECK(test_game.bad_turn({i, -1}) == true);
    }
    for (int i = 0; i < 10; i++) {
        CHECK(test_game.bad_turn({10, i}) == true);
        CHECK(test_game.bad_turn({-1, i}) == true);
    }
    CHECK(test_game.bad_turn({-2, -2}) == true);
    CHECK(test_game.bad_turn({10, 10}) == true);
}
TEST_CASE("If it's OK to change an empty cell") {
    Game test_game;
    for (int i = 0; i < 10; i += 2) {
        for (int j = 0; j < 10; j += 2) {
            CHECK(test_game.bad_turn({i, j}) == false);
        }
    }
}
TEST_CASE("If you try to change a cell that you have already gone to") {
    Game test_game;
    for (int i = 0; i < 10; i += 2) {
        // to be sure, that there be no random win
        for (int j = 0; j < 10; j += 2) {
            test_game.turn({i, j});
        }
    }
    for (int i = 0; i < 10; i += 2) {
        for (int j = i; j < 10; j += 2) {
            CHECK(test_game.bad_turn({i, j}));
        }
    }
}
TEST_CASE("Horizontal-victory") {
    Game test_game_first;
    for (int i = 0; i < 4; i++) {
        test_game_first.turn({0, i});
        test_game_first.turn({1, i});
    }
    test_game_first.turn({0, 4});
    CHECK(test_game_first.is_victory() == true);
    Game test_game_second;
    test_game_second.turn({0, 0});
    for (int i = 9; i >= 6; i--) {
        test_game_second.turn({9, i});
        test_game_second.turn({8, i});
    }
    test_game_second.turn({9, 5});
    CHECK(test_game_second.is_victory() == true);
}
TEST_CASE("Vertical-victory") {
    Game test_game_first;
    for (int i = 0; i < 9; i++) {
        test_game_first.turn({i, 0});
        test_game_first.turn({i, 1});
    }
    test_game_first.turn({9, 0});
    CHECK(test_game_first.is_victory() == true);
    Game test_game_second;
    test_game_second.turn({0, 0});
    for (int i = 9; i >= 6; i--) {
        test_game_second.turn({i, 9});
        test_game_second.turn({i, 8});
    }
    test_game_second.turn({5, 9});
    CHECK(test_game_second.is_victory() == true);
}
TEST_CASE("Diagonal-victory(like f(x) = x)") {
    Game test_game_first;
    for (int i = 0; 4 > i; i++) {
        test_game_first.turn({i, i});
        test_game_first.turn({i + 1, i});
    }
    test_game_first.turn({4, 4});
    CHECK(test_game_first.is_victory() == true);
    Game test_game_second;
    for (int i = 0; i < 4; i++) {
        test_game_second.turn({5 + i, 5 + i});
        test_game_second.turn({4 + i, 5 + i});
    }
    test_game_second.turn({4, 4});
    CHECK(test_game_second.is_victory() == true);
}
TEST_CASE("Check draw") {
    Game test_game;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            test_game.turn({4 * i, j});
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            test_game.turn({4 * i + 1, j});
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 9; j >= 0; j--) {
            test_game.turn({4 * i + 3, j});
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 9; j >= 0; j--) {
            test_game.turn({4 * i + 2, j});
        }
    }
    CHECK(test_game.is_victory() == false);
    CHECK(test_game.is_ended() == 1);
}
TEST_CASE("Victory last turn") {
    Game test_game;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            test_game.turn({4 * i, j});
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            test_game.turn({4 * i + 1, j});
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 9; j >= 0; j--) {
            test_game.turn({4 * i + 3, j});
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 9; j >= 0; j--) {
            test_game.turn({4 * i + 2, j});
        }
    }
    for (int i = 0; i < 4; i++) {
        test_game.turn({9, i});
        test_game.turn({9, i + 5});
    }
    test_game.turn({9, 9});
    test_game.turn({9, 4});
    CHECK(test_game.is_ended() == 1);
}
}  // namespace tictactoe
