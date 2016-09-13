#include <type_traits>

#include "board.hpp"
#include "game.hpp"
#include "simulation.hpp"

int main(int argc, char **argv)
{
    using game_moves = List<
                            Move<0, 0>,
                            Move<1, 1>,
                            Move<0, 1>,
                            Move<2, 0>,
                            Move<0, 2>,
                            Move<2, 2>,
                            Move<2, 1>
                           >;

    using last_state = simulate_t<game_moves>;
    Printer<last_state>::print();
    return 0;
}
