#pragma once

#include "winner_check.hpp"

template <class State, class GameMoves>
class ProcessGame;

template <class State>
struct ProcessGame<State, List<>>
{
    using Type = State;
};

template <class State, unsigned x, unsigned y, class... Xs>
struct ProcessGame<State, List<Move<x, y>, Xs...>>
{
    using NewState = make_move_t<State, x, y>;
    using Type = typename std::conditional<IsWin<NewState, x, y, 3>::value,
                                  NewState,
                                  typename ProcessGame<NewState, List<Xs...>>::Type>::type;
}; 

template <class State, class GameMoves>
using process_game_t = typename ProcessGame<State, GameMoves>::Type;

template <class GameMoves>
struct Simulate
{
    using Type = process_game_t<GameState<board::clean_board_t<3, 3>, Player::Player1>, GameMoves>;
};

template <class GameMoves>
using simulate_t = typename Simulate<GameMoves>::Type;
