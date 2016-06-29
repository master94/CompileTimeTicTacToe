#pragma once

#include <type_traits>
#include "board.hpp"

using namespace board;

template <class Board, int posX, int posY, int dirX, int dirY, class StateWrapper, class Enable = void>
struct Count
{
    enum {
        value = 0
    };
};

template <unsigned w, unsigned h, class List, int posX, int posY, int dirX, int dirY, State state>
struct Count<Board<w, h, List>, posX, posY, dirX, dirY, StateWrapper<state>, typename std::enable_if<posX >= 0 && posY >= 0 && posX < w && posY < h>::type>
{
    enum {
        value = std::is_same<board::get_t<posX, posY, Board<w, h, List>>, StateWrapper<state>>::value
                + Count<Board<w, h, List>, posX + dirX, posY + dirY, dirX, dirY, StateWrapper<state>>::value
    };
};

template <class Board, int posX, int posY, int dirX, int dirY>
struct CountBiDir
{
    enum {
        value =   Count<Board, posX, posY, +dirX, +dirY, board::get_t<posX, posY, Board>>::value
                + Count<Board, posX, posY, -dirX, -dirY, board::get_t<posX, posY, Board>>::value
                - 1
    };
};

template <class GameState, unsigned posX, unsigned posY, unsigned winLineLen>
struct IsWin;

template <class Board, Player player, unsigned posX, unsigned posY, unsigned winLineLen>
struct IsWin<GameState<Board, player>, posX, posY, winLineLen>
{
    enum {
        value =    CountBiDir<Board, posX, posY, +1, +0>::value >= winLineLen
                || CountBiDir<Board, posX, posY, +0, +1>::value >= winLineLen
                || CountBiDir<Board, posX, posY, +1, +1>::value >= winLineLen
                || CountBiDir<Board, posX, posY, +1, -1>::value >= winLineLen
    };
};
