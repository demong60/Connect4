#include "Util.h"

Game MinMax(bool who_plays);
Game AlphaBeta(bool who_plays);
Game MonteCarlo(bool who_plays);
void test_ab_vs_mcts(bool debug, int tries);

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main() {
    srand(time(NULL));

    int cl = system("clear");

    cout << "Select the algorithm the bot will use: \n"
         << "(0) MiniMax\n"
         << "(1) MiniMax with Alpha-Beta Pruning\n"
         << "(2) Monte Carlo Tree Search\n";
    int algo = 0;
    cin >> algo;

    cl = system("clear");

    cout << "Select who goes first:\n"
         << "(0) Computer\n"
         << "(1) Player\n";

    bool who_plays = false;  // true = PLAYER   ||   false = COMPUTER
    cin >> who_plays;

    Game game;
    switch (algo) {
        case 0:
            game = MinMax(who_plays);
            break;
        case 1:
            game = AlphaBeta(who_plays);
            break;
        case 2:
            game = MonteCarlo(who_plays);
            break;
        default:
            game = MinMax(who_plays);
            break;
    }

    if (Util::CheckForWin(game, game.move_played)) {
        vector<pair<int, int>> winning_positions = Util::GetWinSegment(game, game.move_played);
        Util::PrintVictoriousGame(game);
        char VICTOR = game.board[game.positions_played[game.move_played]][game.move_played];
        if (VICTOR == 'X') {
            cout << (algo == 3 ? "MCTS won" : "COMPUTER won") << '\n';
        } else {
            cout << (algo == 3 ? "Alpha-beta won" : "YOU WIN!!!") << '\n';
        }
    } else
        cout << "EMPATE\n";
}

Game MinMax(bool who_plays) {
    int last_played;

    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    Util::PrintGame(game);
    do {
        if (who_plays) {
            ms_double = t2 - t1;
            cout << "Move " << game.counter << " created " << Util::node_count << " nodes and took " << ms_double.count() << " milliseconds.\n";
        }
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played;
            if (!Util::MakeMove(last_played, game, PLAYER)) {
                do {
                    cout << "Ilegal Move. Please choose a possible: ";
                    cin >> last_played;
                } while (!Util::MakeMove(last_played, game, PLAYER));
            }
        } else {
            cout << "Computer playing...\n";
            t1 = high_resolution_clock::now();
            int best_move = Algorithms::MinMax(game);
            t2 = high_resolution_clock::now();
            Util::MakeMove(best_move, game, COMPUTER);
        }

        Util::PrintGame(game);
        who_plays = !who_plays;
    } while (!Util::CheckForWin(game, game.move_played) && game.counter != 42);

    return game;
}

Game MonteCarlo(bool who_plays) {
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    int last_played;
    shared_ptr<Node> root = make_shared<Node>(game, who_plays == 0 ? PLAYER : COMPUTER);
    root->Expand();

    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    Util::PrintGame(root->game);
    do {
        if (who_plays) {
            ms_double = t2 - t1;
            cout << "Move " << game.counter << " created " << Util::node_count << " nodes and took " << ms_double.count() << " milliseconds.\n";
        }
        if (who_plays) {
            if (root->game.counter == 0)  // For when the player starts
                Algorithms::Expand(root);

            cout << "Player's turn\n";
            cin >> last_played;
            if (!Util::MakeMove(last_played, root->game, PLAYER)) {
                do {
                    cout << "Ilegal Move. Please choose a possible: ";
                    cin >> last_played;
                } while (!Util::MakeMove(last_played, root->game, PLAYER));
            }

        } else {
            cout << "Computer playing...\n";

            t1 = high_resolution_clock::now();
            last_played = Algorithms::MonteCarloTreeSearch(root);
            t2 = high_resolution_clock::now();
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
    } while (!Util::CheckForWin(root->game, root->game.move_played) && game.counter != 42);

    return root->game;
}

Game AlphaBeta(bool who_plays) {
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    int last_played;
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    Util::PrintGame(game);
    do {
        if (who_plays) {
            ms_double = t2 - t1;
            cout << "Move " << game.counter << " created " << Util::node_count << " nodes and took " << ms_double.count() << " milliseconds.\n";
        }
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played;
            if (!Util::MakeMove(last_played, game, PLAYER)) {
                do {
                    cout << "Ilegal Move. Please choose a possible: ";
                    cin >> last_played;
                } while (!Util::MakeMove(last_played, game, PLAYER));
            }
        } else {
            cout << "Computer playing...\n";
            t1 = high_resolution_clock::now();
            last_played = Algorithms::MinMaxWithAlphaBetaPruning(game);
            t2 = high_resolution_clock::now();
            Util::MakeMove(last_played, game, COMPUTER);
        }

        Util::PrintGame(game);
        who_plays = !who_plays;
    } while (!Util::CheckForWin(game, game.move_played) && game.counter != 42);

    return game;
}
