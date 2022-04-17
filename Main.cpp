#include "Util.h"

void min_max();
void alfa_beta();

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // min_max();
    alfa_beta();
}

void min_max() {
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
    if(Util::CheckForWin(game, game.move_played)){
        Util::PrintGame(game); // PRINT WIN COLORS 
    }
    // srand(time(NULL));
}

void alfa_beta() {
    Game game_ab;
    game_ab.depth = 0;
    game_ab.counter = 0;
    game_ab.move_played = 3;

    int cl = system("clear");
    cout << "Select who goes first:\n"
         << "(0) Computer\n"
         << "(1) Player\n";
    bool who_plays = false;  // true = PLAYER   ||   false = COMPUTER
    // cin >> who_plays;
    int last_played_ab;

    Util::PrintGame(game_ab);
    do {
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played_ab;
            Util::MakeMove(last_played_ab, game_ab, PLAYER);
            game_ab.move_played = last_played_ab;
        } else {
            cout << "Computer playing...\n";
            last_played_ab = Algorithms::MinMaxWithAlphaBetaPruning(game_ab);
            Util::MakeMove(last_played_ab, game_ab, COMPUTER);
        }

        Util::PrintGame(game_ab);
        who_plays = !who_plays;
    } while (!Util::CheckForWin(game_ab, game_ab.move_played));
    if(Util::CheckForWin(game_ab, game_ab.move_played)){
        Util::PrintGame(game_ab); // PRINT WIN COLORS
    }
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