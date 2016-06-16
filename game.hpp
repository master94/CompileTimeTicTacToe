#pragma once

#include "printer.hpp"
#include "board.hpp"

enum class Player
{
    Player1,
    Player2
};

template <class Board, Player turn>
struct GameState;

template <class Board>
struct IsWin
{
    enum {
        value = false
    };
};

template <Player player>
struct CellStateForPlayer;

template <>
struct CellStateForPlayer<Player::Player1>
{
    static const State state = State::X;
};

template <>
struct CellStateForPlayer<Player::Player2>
{
    static const State state = State::O;
};

template <Player player>
struct NextTurn;

template <>
struct NextTurn<Player::Player1>
{
    static const Player player = Player::Player2;
};

template <>
struct NextTurn<Player::Player2>
{
    static const Player player = Player::Player1;
};

template <class GameState, unsigned x, unsigned y>
struct MakeMove;

template <class Board, Player turn, unsigned x, unsigned y>
struct MakeMove<GameState<Board, turn>, x, y>
{
    using Type = GameState<board::set_t<x, y, CellStateForPlayer<turn>::state, Board>, NextTurn<turn>::player>;
};

template <class GameState, unsigned x, unsigned y>
using make_move_t = typename MakeMove<GameState, x, y>::Type;

template <class Board, Player player>
struct Printer<GameState<Board, player>>
{
    static void print()
    {
        Printer<Board>::print();
    }
};
