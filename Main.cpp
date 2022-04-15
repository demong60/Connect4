#include "Util.h"
/* Leave the algorithm we want to use uncommented */
// #define MONTE_CARLO
//#define ALPHA_BETA
// #define MINIMAX

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    int i = 1;  // Even == PLAYER starts Odd == COMPUTER starts
    int last_played;

    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    do {
        if (i++ % 2 == 0) {
            cout << "Player's turn\n";
            cin >> last_played;
            Util::MakeMove(last_played, game, PLAYER);
        } else {
            cout << "Computer playing...\n";

            vector<Game> possible_moves;
            Util::CreateChildren(game, possible_moves, COMPUTER);

            int best_value = INT_MIN;
            int best_move;

            for (Game child : possible_moves) {
                int move_score = Algorithms::NewMinMax(child, MAX_DEPTH, false);
                if (move_score > best_value) {
                    best_value = move_score;
                    best_move = child.move_played;
                }
            }
            Util::MakeMove(best_move, game, COMPUTER);
        }

        Util::PrintGame(game);
    } while (!Util::CheckForWin(game, game.move_played));

    srand(time(NULL));
}

// NAO APAGAR

// vector<int> moveList;
// shared_ptr<Node> root = make_shared<Node>(game, PLAYER);
// root->parent = nullptr;

// do {
//     if (i % 2 == 0) {
//         cout << "Player's turn\n";
//         cin >> last_played;
//     } else {
//         cout << "Computer playing...\n";
//         last_played = Algorithms::MonteCarloTreeSearch(root);
//     }

// for (auto child : root->children) {
//     if (child->game.move_played == last_played) {
//         root = child;
//         break;
//     }
// }
// root->parent = nullptr;
// Util::PrintGame(root->game);
// cout << last_played << "\n";

// ----------------------------------------------------------

// int moves[] = {3, 2, 4, 6, 5, 0};
// for (int m : moves) {
//     Util::MakeMove(m, game, ((i++) % 2 == 0 ? PLAYER : COMPUTER));
// }

// Util::PrintGame(game);
// vector<Game> children;
// Util::CreateChildren(game, children, COMPUTER);
// cout << children.size() << "\n";
// cin.get();
// for (Game child : children) {
//     Util::PrintGame(child);
//     cout << Util::UtilityFunction(child, child.move_played, COMPUTER) << "\n";
// }