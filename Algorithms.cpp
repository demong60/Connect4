#include "Algorithms.h"

// No more than 10 for alfa-beta or it takes too long.. :-(
const int MAX_ITER = 11;  // para mudar temporariamente a search do alfa-beta (no fim retirar)

int Algorithms::MinMax(Game &game) {
    // ========================================================
    /*
        Para já os nossos min-max e alpha-beta dependem de
        que o game.move_played seja uma posição entre 0 e 6
        Se não fizermos esta linha a posição vai ser random - ex: 321224 (que obviamente está fora do indice do array)
        e por isso daria seg-fault
        podemos evitar ter de fazer isto, mas temos de arranjar uma alternativa para a primeira jogada
        ou fazer um if_statement em baixo
    */
    // if (game.depth == 0)
    //      return (WIDTH - 1) / 2;
    // game.depth = 0;
    // ========================================================
    pair<int, int> res = MaxValue(game);
    cout << res.first << " " << res.second << "\n";
    return res.second;
}

pair<int, int> Algorithms::MaxValue(Game &game) {
    if (game.depth == MAX_DEPTH || Util::CheckForWin(game, game.move_played) || game.counter == 42)
        return {Util::UtilityFunction(game, game.move_played), game.move_played};

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

int Algorithms::NewMinMax(Game &game, int depth, bool is_maximizing) {
    if (depth == 0 || Util::CheckForWin(game, game.move_played) || game.counter == 42)
        return Util::UtilityFunction(game, game.move_played);

    if (is_maximizing) {
        int best_value = INT_MIN;
        vector<Game> children;
        Util::CreateChildren(game, children, PLAYER);
        for (Game child : children) {
            int value = NewMinMax(child, depth - 1, false);
            best_value = max(best_value, value);
        }
        return best_value;
    } else {
        int best_value = INT_MAX;
        vector<Game> children;
        Util::CreateChildren(game, children, COMPUTER);
        for (Game child : children) {
            int value = NewMinMax(child, depth - 1, true);
            best_value = min(best_value, value);
        }
        return best_value;
    }
}

// {score, movePlayed}
pair<int, int> Algorithms::MinValue(Game &game) {
    if (game.depth == MAX_DEPTH || Util::CheckForWin(game, game.move_played) || game.counter == 42)
        return {Util::UtilityFunction(game, game.move_played), game.move_played};

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
    game.depth = 0;
    int alpha = INT_MIN, beta = INT_MAX;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    pair<int, int> ans = {INT_MIN, -1};
    for(auto child : children){
        child.depth = 0;
        int res = Algorithms::MinValue(child, alpha, beta);
        if(res > ans.first){
            ans.first = res;
            ans.second = child.move_played;
        }
    }
    return ans.second;
}
    
    
    

int Algorithms::MaxValue(Game &game, int alpha, int beta) {
    if (game.depth == MAX_ITER)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return -512;
    if (game.counter == 42) return 0;

    int value = INT_MIN;
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        int cur = MinValue(child, alpha, beta);

        if (cur > value) value = cur;
        if (cur >= beta) return beta;
        if (cur > alpha) alpha = cur;
    }

    return value;
}

// {score, movePlayed}
int Algorithms::MinValue(Game &game, int alpha, int beta) {
    if (game.depth == MAX_ITER)
        return Util::UtilityFunction(game, game.move_played);
    if (Util::CheckForWin(game, game.move_played)) return 512;
    if (game.counter == 42) return 0;

    int value = INT_MAX;
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        int cur = MaxValue(child, alpha, beta);

        if (cur < value) value = cur;
        if (cur <= alpha) return alpha;
        if (cur < beta) beta = cur;
    }

    return value;
}
