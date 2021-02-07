#ifndef GAME_H_
#define GAME_H_

#include <utility>
#include <vector>

namespace tictactoe {
struct Game {
    static const int HEIGHT = 10;
    static const int WIDTH = 10;
    static const int ROW_TO_WIN = 5;
    enum Cell { first_player = 'O', second_player = 'X', none = '.' };

private:
    bool cur_player = false;  // 0 - first player, 1 - the second one
    int num_of_turns = 0;
    std::vector<std::vector<Cell>> field;
    static int to_int(Cell a);

public:
    Game();
    [[nodiscard]] bool is_victory() const;
    [[nodiscard]] int is_ended() const;
    [[nodiscard]] bool bad_turn(std::pair<int, int> a) const;
    [[nodiscard]] Cell get_value(std::pair<int, int> a) const;
    [[nodiscard]] bool get_player() const;
    void turn(std::pair<int, int> a);
};

void play();
}  // namespace tictactoe

#endif  // GAME_H_
