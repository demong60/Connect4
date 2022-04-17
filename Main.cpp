#include "Util.h"

Game MinMax(bool who_plays);
Game AlphaBeta(bool who_plays);
Game MonteCarlo(bool who_plays);

int main() {
    srand(time(NULL));

    int cl = system("clear");
    cout << "Select who goes first:\n"
         << "(0) Computer\n"
         << "(1) Player\n";

    bool who_plays = false;  // true = PLAYER   ||   false = COMPUTER
    cin >> who_plays;

    Game game;
    // game = MinMax(who_plays);
    // game = MonteCarlo(who_plays);
    game = AlphaBeta(who_plays);

    if (Util::CheckForWin(game, game.move_played)) {
        vector<pair<int, int>> winning_positions = Util::GetWinSegment(game, game.move_played);
        Util::PrintVictoriousGame(game);
    }
}

Game MinMax(bool who_plays) {
    int last_played;

    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    do {
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played;
            Util::MakeMove(last_played, game, PLAYER);
        } else {
            cout << "Computer playing...\n";
            int best_move = Algorithms::MinMax(game);
            Util::MakeMove(best_move, game, COMPUTER);
        }

        Util::PrintGame(game);
    } while (!Util::CheckForWin(game, game.move_played));

    return game;
}

Game MonteCarlo(bool who_plays) {
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    int last_played;
    shared_ptr<Node> root = make_shared<Node>(game, PLAYER);

    Util::PrintGame(game);
    do {
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played;
        } else {
            cout << "Computer playing...\n";
            last_played = Algorithms::MonteCarloTreeSearch(root);
        }

        for (auto child : root->children) {
            if (child->game.move_played == last_played) {
                root = child;
                root->parent = nullptr;
                break;
            }
        }
        Util::PrintGame(root->game);
        who_plays = !who_plays;
    } while (!Util::CheckForWin(root->game, root->game.move_played));

    return root->game;
}

Game AlphaBeta(bool who_plays) {
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    int last_played;
    Util::PrintGame(game);
    do {
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played;
            Util::MakeMove(last_played, game, PLAYER);
            game.move_played = last_played;
        } else {
            cout << "Computer playing...\n";
            last_played = Algorithms::MinMaxWithAlphaBetaPruning(game);
            Util::MakeMove(last_played, game, COMPUTER);
        }

        Util::PrintGame(game);
        who_plays = !who_plays;
    } while (!Util::CheckForWin(game, game.move_played));

    return game;
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