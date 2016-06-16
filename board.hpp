#pragma once

#include "list.hpp"
#include "printer.hpp"

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

// ----------------------------------------------------------------------------

template <bool cond>
struct PrintNL
{
    static void print() {}
};

template <>
struct PrintNL<true>
{
    static void print()
    {
        std::cout << std::endl;
    }
};

template <class Board, unsigned pos>
struct BoardPrinter;

template <unsigned w, unsigned h, unsigned pos, class X, class... Xs>
struct BoardPrinter<Board<w, h, List<X, Xs...>>, pos>
{
    static void print()
    {
        Printer<X>::print();
        PrintNL<(pos + 1) % w == 0>::print();
        BoardPrinter<Board<w, h, List<Xs...>>, pos + 1>::print();
    }
};

template <unsigned w, unsigned h, unsigned pos>
struct BoardPrinter<Board<w, h, List<>>, pos>
{
    static void print() {}
};

} // board


template <unsigned w, unsigned h, class ElemList>
struct Printer<board::Board<w, h, ElemList>>
{
    static void print()
    {
        board::BoardPrinter<board::Board<w, h, ElemList>, 0>::print();
    }
};

template <>
struct Printer<Empty>
{
    static void print()
    {
        std::cout << ".";
    }
};

template <>
struct Printer<O>
{
    static void print()
    {
        std::cout << "O";
    }
};

template <>
struct Printer<X>
{
    static void print()
    {
        std::cout << "X";
    }
};
