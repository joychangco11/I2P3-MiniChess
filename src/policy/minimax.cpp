#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief get a legal action using Minimax policy
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int Minimax::minimax(State* state, int depth, bool isMaximizingPlayer) {
    if (depth == 0 || state->game_state != NONE) {
        return state->evaluate();
    }

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (auto& move : state->legal_actions) {
            State* newState = state->next_state(move);
            int eval = minimax(newState, depth - 1, false);
            maxEval = std::max(maxEval, eval);
            delete newState;
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (auto& move : state->legal_actions) {
            State* newState = state->next_state(move);
            int eval = minimax(newState, depth - 1, true);
            minEval = std::min(minEval, eval);
            delete newState;
        }
        return minEval;
    }
}

Move Minimax::get_move(State* state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    int maxEval = INT_MIN;
    Move bestMove;
    for (auto& move : state->legal_actions) {
        State* newState = state->next_state(move);
        int eval = minimax(newState, depth - 1, true);
        if (eval > maxEval) {
            maxEval = eval;
            bestMove = move;
        }
        delete newState;
    }
    return bestMove;
}