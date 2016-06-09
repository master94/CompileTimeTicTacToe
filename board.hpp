#pragma once

#include "list.hpp"

struct Empty;
struct X;
struct O;

namespace board
{

template <unsigned w, unsigned h, class List>
struct Board;

template <unsigned w, unsigned h, class...Elems>
struct Board<w, h, List<Elems...>>
{
    using Type = List<Elems...>;
};

template <unsigned w, unsigned h>
using clean_board_t = Board<w, h, create_list_t<w * h, Empty>>;

// ----------------------------------------------------------------------------


template <unsigned x, unsigned y, class Board>
struct Get;

template <unsigned x, unsigned y, unsigned w, unsigned h, class List>
struct Get<x, y, Board<w, h, List>>
{
    using Type = get_t<y * w + x, List>; 
};

template <unsigned x, unsigned y, class Board>
using get_t = typename Get<x, y, Board>::Type;


// ----------------------------------------------------------------------------

template <unsigned x, unsigned y, class Player, class Board>
struct Set;

template <unsigned x, unsigned y, class Player, unsigned w, unsigned h, class List>
struct Set<x, y, Player, Board<w, h, List>>
{
    using Type = Board<w, h, put_t<y * w + x, Player, List>>;
};

template <unsigned x, unsigned y, class Player, class Board>
using set_t = typename Set<x, y, Player, Board>::Type;

} // board
