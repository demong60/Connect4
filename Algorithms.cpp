#include "Algorithms.h"

int Algorithms::MinMax(Game &game) {
    vector<Game> possible_moves;
    Util::CreateChildren(game, possible_moves, COMPUTER);

    int best_value = INT_MIN;
    int best_move;

    for (Game child : possible_moves) {
        int move_score = Algorithms::MinValue(child, MAX_DEPTH);
        if (move_score > best_value) {
            best_value = move_score;
            best_move = child.move_played;
        }
    }
    return best_move;
}

int Algorithms::MaxValue(Game &game, int depth) {
    if (depth == 0 || Util::CheckForWin(game, game.move_played) || game.counter == 42)
        return Util::UtilityFunction(game, game.move_played);

    int best_value = INT_MIN;
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        int value = MinValue(child, depth - 1);
        best_value = max(best_value, value);
    }
    return best_value;
}

int Algorithms::MinValue(Game &game, int depth) {
    if (depth == 0 || Util::CheckForWin(game, game.move_played) || game.counter == 42)
        return Util::UtilityFunction(game, game.move_played);

    int best_value = INT_MAX;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        int value = MaxValue(child, depth - 1);
        best_value = min(best_value, value);
    }
    return best_value;
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
    bool done = false;
    // if (root->game.depth == 0) {
    //     best_move = 3;
    //     done = true;
    // }
    for (int i = 0; i < 10'000'000; i++) {
        shared_ptr<Node> node = Algorithms::Select(root);
        if (!Util::CheckForWin(node->game, node->game.move_played) && node->game.counter < 42)
            Algorithms::Expand(node);

        if (node->children.size() > 0)
            node = node->children[0];

        int value = Algorithms::Simulate(*node);
        Algorithms::Backpropagate(*node, value);
    }

    int max_total_playouts = INT_MIN;
    if (!done) {
        for (shared_ptr<Node> child : root->children) {
            if (child->visited > max_total_playouts) {
                max_total_playouts = child->visited;
                best_move = child->game.move_played;
            }
        }
    }

    return best_move;
}

int Algorithms::MinMaxWithAlphaBetaPruning(Game &game) {
    int alpha = INT_MIN, beta = INT_MAX;
    int MAX_ITER = 10;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    pair<int, int> ans = {INT_MIN, -1};
    for (auto child : children) {
        int res = Algorithms::MinValue(child, MAX_ITER, alpha, beta);
        if (res > ans.first) {
            ans.first = res;
            ans.second = child.move_played;
        }
    }
    return ans.second;
}

int Algorithms::MaxValue(Game &game, int depth, int alpha, int beta) {
    if (depth == 0)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return -512 + game.depth;
    if (game.counter == 42) return 0;

    int value = INT_MIN;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        int cur = MinValue(child, depth - 1, alpha, beta);

        if (cur > value) value = cur;
        if (cur >= beta) return beta;
        if (cur > alpha) alpha = cur;
    }

    return value;
}

int Algorithms::MinValue(Game &game, int depth, int alpha, int beta) {
    if (depth == 0)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return 512 - game.depth;
    if (game.counter == 42) return 0;

    int value = INT_MAX;
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        int cur = MaxValue(child, depth - 1, alpha, beta);

        if (cur < value) value = cur;
        if (cur <= alpha) return alpha;
        if (cur < beta) beta = cur;
    }

    return value;
}
