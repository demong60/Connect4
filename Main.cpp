#include "Util.h"

Game MinMax(bool who_plays);
Game AlphaBeta(bool who_plays);
Game MonteCarlo(bool who_plays);
Game MonteCarlo_MinMaxAB(bool who_plays);

int main() {
    srand(time(NULL));

    int cl = system("clear");

    cout << "Select the algorithm the bot will use: \n"
         << "(0) MiniMax\n"
         << "(1) MiniMax with Alpha-Beta Pruning\n"
         << "(2) Monte Carlo Tree Search\n"
         << "(3) MCTS vs MiniMax with Alpha-Beta Pruning\n";
    int algo = 0;
    cin >> algo;

    cl = system("clear");

    if (algo != 3)
        cout << "Select who goes first:\n"
             << "(0) Computer\n"
             << "(1) Player\n";
    else
        cout << "Select who goes first:\n"
             << "(0) Monte Carlo Tree Search\n"
             << "(1) Min-Max with Alpha-Beta Pruning\n";

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
        case 3:
            game = MonteCarlo_MinMaxAB(who_plays);
            break;
        default:
            game = MinMax(who_plays);
            break;
    }

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
        Util::PrintGame(game);
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
        who_plays = !who_plays;
    } while (!Util::CheckForWin(game, game.move_played));

    return game;
}

Game MonteCarlo(bool who_plays) {
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    int last_played;
    shared_ptr<Node> root = make_shared<Node>(game, who_plays == 0 ? PLAYER : COMPUTER);

    do {
        Util::PrintGame(root->game);
        if (who_plays) {
            cout << "Player's turn\n";
            cin >> last_played;
            if (root->game.counter == 0)  // For when the player starts
                Algorithms::Expand(root);
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

Game MonteCarlo_MinMaxAB(bool who_plays) {
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    int last_played;
    shared_ptr<Node> root = make_shared<Node>(game, who_plays == 0 ? PLAYER : COMPUTER);

    do {
        Util::PrintGame(root->game);
        if (who_plays) {
            cout << "MinMax playing\n";
            last_played = Algorithms::MinMaxWithAlphaBetaPruning(root->game);
            if (root->game.counter == 0)  // For when the player starts
                Algorithms::Expand(root);
        } else {
            cout << "MCTS playing...\n";
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