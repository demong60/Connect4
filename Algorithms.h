#pragma once
#include "Util.h"

class Algorithms {
    /**
     * @brief Applies the MinMax tree search to the given game and returns the best move
     *
     * @param game
     */
    int MinMax(Game &game);

    /**
     * @brief Applies the MinMax tree search WITH Alpha Beta Pruning to the given game and returns the best move
     *
     * @param game
     */
    int MinMaxWithAlphaBetaPruning(Game &game);

    /**
     * @brief Applies the Monte Carlo tree search to the given game and returns the best move
     *
     * @param game
     */
    int MonteCarloTreeSearch(Game &game);
};