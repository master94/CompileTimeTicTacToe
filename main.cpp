#include <type_traits>

#include "board.hpp"

int main(int argc, char **argv)
{
    using b1 = board::set_t<1, 1, O, board::clean_board_t<3, 3>>;
    Printer<b1>::print();
    return 0;
}
