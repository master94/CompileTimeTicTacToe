#include <type_traits>

#include "board.hpp"
#include "game.hpp"

int main(int argc, char **argv)
{
    using start_board = board::clean_board_t<3, 3>;
    using game_state = GameState<start_board, Player::Player1>;
    using s1 = make_move_t<game_state, 1, 1>;
    using s2 = make_move_t<s1, 0, 0>;
    using s3 = make_move_t<s2, 2, 2>;
    using s4 = make_move_t<s3, 2, 0>;
    Printer<s4>::print();
    return 0;
}
