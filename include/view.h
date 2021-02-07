#ifndef VIEW_H_
#define VIEW_H_

#include <iostream>
#include "game.h"

namespace tictactoe {
struct View {
    void draw_result() const;

    static void bad_comment();

    [[nodiscard]] bool read_turn();

    void drawing() const;

    void draw_board() const;

    explicit View(Game &game);

private:
    Game &game_;
};
}  // namespace tictactoe

#endif  // VIEW_H_
