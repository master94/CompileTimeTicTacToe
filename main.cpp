#include <type_traits>

#include "board.hpp"
#include "game.hpp"
#include "winner_check.hpp"


int main(int argc, char **argv)
{
    using start_board = board::clean_board_t<3, 3>;
    using game_state = GameState<start_board, Player::Player1>;
    using s1 = make_move_t<game_state, 1, 1>;
    using s2 = make_move_t<s1, 0, 0>;
    using s3 = make_move_t<s2, 2, 2>;
    using s4 = make_move_t<s3, 2, 0>;
    using s5 = make_move_t<s4, 0, 1>;
    using s6 = make_move_t<s5, 1, 0>;
    static_assert(IsWin<s6, 1, 0, 3>::value == 1, "Error");
    Printer<s6>::print();
    return 0;
}
