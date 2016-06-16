#include <type_traits>

#include "board.hpp"

int main(int argc, char **argv)
{
    using start_board = board::clean_board_t<3, 3>;
    using b1 = board::set_t<1, 1, State::O, start_board>;
    using b2 = board::set_t<0, 0, State::X, b1>;
    Printer<b2>::print();
    return 0;
}
