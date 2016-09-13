#pragma once

#include "printer.hpp"
#include "board.hpp"

template <unsigned x, unsigned y>
class Move;

enum class Player
{
    Player1,
    Player2
};

template <Player player>
struct PlayerWrapper;

template <class Board, Player turn>
struct GameState;

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

template <>
struct Printer<PlayerWrapper<Player::Player1>>
{
    static void print()
    {
        std::cout << "Player #1" << std::endl;
    }
};

template <>
struct Printer<PlayerWrapper<Player::Player2>>
{
    static void print()
    {
        std::cout << "Player #2" << std::endl;
    }
};

template <class Board, Player player>
struct Printer<GameState<Board, player>>
{
    static void print()
    {
        std::cout << "Board state:" << std::endl;
        Printer<Board>::print();
        std::cout << std::endl << "Winner:" << std::endl;
        Printer<PlayerWrapper<NextTurn<player>::player>>::print();
    }
};
