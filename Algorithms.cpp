#include "Algorithms.h"

int Algorithms::MinMax(Game &game) {
    //    if (game.depth == 0)
    //      return (WIDTH - 1) / 2;
    game.depth = 0;
    pair<int, int> res = MaxValue(game);
    cout << res.first << " " << res.second << "\n";
    return res.second;
}

pair<int, int> Algorithms::MaxValue(Game &game) {
    if (game.depth == MAX_DEPTH)
        return {Util::UtilityFunction(game, game.move_played, PLAYER), game.move_played};
    if (Util::CheckForWin(game, game.move_played, PLAYER)) return {-512, game.move_played};
    if (Util::CheckForWin(game, game.move_played, COMPUTER)) return {512, game.move_played};
    if (game.counter == 42) return {0, game.move_played};

    pair<int, int> value = {INT_MIN, -1};
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        pair<int, int> cur = MinValue(child);

        if (cur.first > value.first)
            value = cur;
    }

    return value;
}

// {score, movePlayed}
pair<int, int> Algorithms::MinValue(Game &game) {
    if (game.depth == MAX_DEPTH)
        return {Util::UtilityFunction(game, game.move_played, COMPUTER), game.move_played};
    if (Util::CheckForWin(game, game.move_played, PLAYER)) return {-512, game.move_played};
    if (Util::CheckForWin(game, game.move_played, COMPUTER)) return {512, game.move_played};
    if (game.counter == 42) return {0, game.move_played};

    pair<int, int> value = {INT_MAX, -1};
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        pair<int, int> cur = MaxValue(child);

        if (cur.first < value.first)
            value = cur;
    }

    return value;
}

int Algorithms::Simulate(Node &node) {
    Node simulation = node;
    int move = rand() % WIDTH;
    while (!Util::CheckForWin(simulation.game, simulation.game.move_played, simulation.symbol) && simulation.game.counter < WIDTH * HEIGHT) {
        move = rand() % WIDTH;
        while (!Util::MakeMove(move, simulation.game, Util::GetNextSymbol(simulation.symbol)))
            move = rand() % WIDTH;
        // Util::PrintGame(simulation.game);
        simulation.symbol = Util::GetNextSymbol(simulation.symbol);
    }

    // Util::PrintGame(simulation.game);

    if (Util::CheckForWin(simulation.game, simulation.game.move_played, simulation.symbol))
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
        if (!Util::CheckForWin(node->game, node->game.move_played, node->symbol) && node->game.counter < 42)
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

int Algorithms::MinMaxWithAlphaBetaPruning(Game &game){
    game.depth = 0;
    pair<int, int> alpha = {INT_MIN, -1}, beta = {INT_MAX, -1};
    pair<int, int> res = Algorithms::MaxValue(game, alpha, beta);
    cout << res.first << " " << res.second << "\n";
    return res.second;
}

pair<int, int> Algorithms::MaxValue(Game &game, pair<int, int> alpha, pair<int, int> beta) {
    if (game.depth == MAX_DEPTH)
        return {Util::UtilityFunction(game, game.move_played, PLAYER), game.move_played};
    // if (Util::CheckForWin(game, game.move_played, PLAYER)) return {-512, game.move_played};
    // if (Util::CheckForWin(game, game.move_played, COMPUTER)) return {512, game.move_played};
    if (game.counter == 42) return {0, game.move_played};

    pair<int, int> value = {INT_MIN, -1};
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        pair<int, int> cur = MinValue(child, alpha, beta);

        if(cur.first > value.first) value = cur;
        if(cur.first >= beta.first) return beta;
        if(cur.first > alpha.first) alpha = cur;
    }

    return value;
}

// {score, movePlayed}
pair<int, int> Algorithms::MinValue(Game &game, pair<int, int> alpha, pair<int, int> beta) {
    if (game.depth == MAX_DEPTH)
        return {Util::UtilityFunction(game, game.move_played, COMPUTER), game.move_played};
    // if (Util::CheckForWin(game, game.move_played, PLAYER)) return {-512, game.move_played};
    // if (Util::CheckForWin(game, game.move_played, COMPUTER)) return {512, game.move_played};
    if (game.counter == 42) return {0, game.move_played};

    pair<int, int> value = {INT_MAX, -1};
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        pair<int, int> cur = MaxValue(child, alpha, beta);

        if(cur.first < value.first) value = cur;
        if(cur.first <= alpha.first) return alpha;
        if(cur.first < beta.first) beta = cur;
    }

    return value;
}

