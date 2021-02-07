#include "view.h"

namespace tictactoe {
View::View(Game &game) : game_(game) {
}

void View::draw_board() const {
    drawing();
}

}  // namespace tictactoe
