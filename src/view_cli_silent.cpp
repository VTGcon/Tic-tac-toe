#include "view.h"

namespace tictactoe {
View::View(Game &game) : game_(game) {
}

void View::draw_board() const {
    if (game_.is_ended() == 0) {
        return;
    }
    drawing();
}
}  // namespace tictactoe
