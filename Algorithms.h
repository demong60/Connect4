#pragma once
#include "Util.h"
#include "Node.h"

namespace Algorithms {
/**
 * @brief Applies the MinMax tree search to the given game and returns the best found move
 *
 * @param game Game to apply Min Max
 * @return int Integer representing the best found move
 */
int MinMax(Game &game);
int MaxValue(Game &game, int depth);
int MinValue(Game &game, int depth);

/**
 * @brief Applies the MinMax tree search WITH Alpha Beta Pruning to the given game and returns the best found move
 *
 * @param game Game to apply Min Max with Alpha beta pruning
 * @return int Integer representing the best found move
 */
int MinMaxWithAlphaBetaPruning(Game &game);
int MaxValue(Game &game, int depth, int alpha, int beta);
int MinValue(Game &game, int depth, int alpha, int beta);

/**
 * @brief Applies the Monte Carlo tree search to the given game and returns the best found move
 *
 * @param root Root of the tree to search using MCTS
 */
int MonteCarloTreeSearch(shared_ptr<Node> root);

int Simulate(Node &node);
void Expand(shared_ptr<Node> node);
void Backpropagate(Node &node, int result);
shared_ptr<Node> Select(shared_ptr<Node> root);

/**
 * @brief Calculates the size of the MCTS tree, used for statistics
 *
 * @param node Root of the tree to be used
 * @return int Integer representing the size of the tree
 */
int GetTreeSize(shared_ptr<Node> root);

}  // namespace Algorithms
