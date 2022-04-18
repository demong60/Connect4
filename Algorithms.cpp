#include "Algorithms.h"

int Algorithms::MinMax(Game &game) {
    Util::node_count = 0;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);

    int best_value = INT_MIN;
    int best_move;
    for (auto child : children) {
        int res = Algorithms::MinValue(child, MAX_DEPTH);
        if (res > best_value) {
            best_value = res;
            best_move = child.move_played;
        }
    }
    return best_move;
}

int Algorithms::MaxValue(Game &game, int depth) {
    if (depth == 0)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return -512;
    if (game.counter == 42) return 0;

    int value = INT_MIN;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        int cur = MinValue(child, depth - 1);

        if (cur > value) value = cur;
    }

    return value;
}

int Algorithms::MinValue(Game &game, int depth) {
    if (depth == 0)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return 512;
    if (game.counter == 42) return 0;

    int value = INT_MAX;
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        int cur = MaxValue(child, depth - 1);

        if (cur < value) value = cur;
    }

    return value;
}

int Algorithms::Simulate(Node &node) {
    Node simulation = node;
    int move = rand() % WIDTH;
    while (!Util::CheckForWin(simulation.game, simulation.game.move_played) && simulation.game.counter < WIDTH * HEIGHT) {
        move = rand() % WIDTH;
        while (!Util::MakeMove(move, simulation.game, Util::GetNextSymbol(simulation.symbol)))
            move = rand() % WIDTH;
        // Util::PrintGame(simulation.game);
        simulation.symbol = Util::GetNextSymbol(simulation.symbol);
    }

    // Util::PrintGame(simulation.game);

    if (Util::CheckForWin(simulation.game, simulation.game.move_played))
        if (simulation.symbol == PLAYER)
            return -1;
        else
            return 1;
    else
        return 0;
}

void Algorithms::Backpropagate(Node &node, int result) {
    node.total += result;
    node.visited++;
    if (node.parent != nullptr)
        Backpropagate(*(node.parent), result);
}

shared_ptr<Node> Algorithms::Select(shared_ptr<Node> node) {
    shared_ptr<Node> temp = node;

    while (temp->children.size() != 0) {
        temp = Util::GetBestUCTChild(temp->children);
    }

    return temp;
}

void Algorithms::Expand(shared_ptr<Node> node) {
    node->Expand();
}

int Algorithms::MonteCarloTreeSearch(shared_ptr<Node> root) {
    int best_move;
    for (int i = 0; i < 1'000'000; i++) {
        shared_ptr<Node> node = Algorithms::Select(root);
        if (!Util::CheckForWin(node->game, node->game.move_played) && node->game.counter < 42)
            Algorithms::Expand(node);

        if (node->children.size() > 0)
            node = node->children[rand() % node->children.size()];

        int value = Algorithms::Simulate(*node);
        Algorithms::Backpropagate(*node, value);
    }

    int max_total_playouts = INT_MIN;
    for (shared_ptr<Node> child : root->children) {
        if (child->visited > max_total_playouts) {
            max_total_playouts = child->visited;
            best_move = child->game.move_played;
        }
    }

    return best_move;
}

int Algorithms::MinMaxWithAlphaBetaPruning(Game &game) {
    Util::node_count = 0;
    int alpha = INT_MIN, beta = INT_MAX;

    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);

    pair<int, int> ans = {INT_MIN, -1};
    int best_value = INT_MIN;
    int best_move;
    for (auto child : children) {
        int res = Algorithms::MinValue(child, MAX_DEPTH_AB, alpha, beta);
        if (res > best_value) {
            best_value = res;
            best_move = child.move_played;
        }
    }
    return best_move;
}

int Algorithms::MaxValue(Game &game, int depth, int alpha, int beta) {
    if (depth == 0)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return -512;
    if (game.counter == 42) return 0;

    int max_eval = INT_MIN;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        int eval = MinValue(child, depth - 1, alpha, beta);

        max_eval = max(eval, max_eval);
        alpha = max(alpha, eval);
        if (beta <= alpha)
            break;
    }

    return max_eval;
}

int Algorithms::MinValue(Game &game, int depth, int alpha, int beta) {
    if (depth == 0)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return 512;
    if (game.counter == 42) return 0;

    int min_eval = INT_MAX;
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        int eval = MaxValue(child, depth - 1, alpha, beta);

        min_eval = min(eval, min_eval);
        beta = min(beta, eval);
        if (beta <= alpha)
            break;
    }

    return min_eval;
}

int Algorithms::GetTreeSize(shared_ptr<Node> node) {
    long long total = 1;
    for (shared_ptr<Node> child : node->children) {
        total += GetTreeSize(child);
    }

    return total;
}
