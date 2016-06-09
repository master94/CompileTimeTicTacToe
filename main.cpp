#include <type_traits>

#include "board.hpp"

int main(int argc, char **argv)
{
    using b1 = board::set_t<1, 1, O, board::clean_board_t<3, 3>>;
    static_assert(std::is_same<board::get_t<1, 1, b1>, X>::value, "Error");
    return 0;
}
