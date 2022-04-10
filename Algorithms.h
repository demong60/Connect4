#pragma once
#include "Util.h"

namespace Algorithms {
/**
 * @brief Applies the MinMax tree search to the given game and returns the best move
 *
 * @param game
 */
int MinMax(Game &game);

pair<int, int> MaxValue(Game &game);

pair<int, int> MinValue(Game &game);

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
}  // namespace Algorithms
