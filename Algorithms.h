#pragma once
#include "Util.h"
#include "Node.h"

namespace Algorithms {
/**
 * @brief Applies the MinMax tree search to the given game and returns the best move
 *
 * @param game
 */
int MinMax(Game &game);

int NewMinMax(Game &game, int depth, bool is_maximizing);

pair<int, int> MaxValue(Game &game);

pair<int, int> MinValue(Game &game);

/**
 * @brief Applies the MinMax tree search WITH Alpha Beta Pruning to the given game and returns the best move
 *
 * @param game
 */
int MinMaxWithAlphaBetaPruning(Game &game);
int MaxValue(Game &game, int depth, int alpha, int beta);
int MinValue(Game &game, int depth, int alpha, int beta);

/**
 * @brief Applies the Monte Carlo tree search to the given game and returns the best move
 *
 * @param game
 */
int MonteCarloTreeSearch(shared_ptr<Node> root);

int Simulate(Node &node);
void Expand(shared_ptr<Node> node);
void Backpropagate(Node &node, int result);
shared_ptr<Node> Select(shared_ptr<Node> root);

}  // namespace Algorithms
