#include "Util.h"
/* Leave the algorithm we want to use uncommented */
// #define MONTE_CARLO
// #define ALPHA_BETA
#define MINIMAX

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    
    #ifdef MONTE_CARLO
    int i = 1;  // Even == PLAYER starts Odd == COMPUTER starts
    int last_played;

    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    // do {
    //     if (i % 2 == 0) {
    //         cout << "Player's turn\n";
    //         cin >> last_played;
    //         Util::MakeMove(last_played, game, PLAYER);
    //     } else {
    //         cout << "Computer playing...\n";
    //         last_played = Algorithms::MonteCarloTreeSearch(game);
    //         Util::MakeMove(last_played, game, COMPUTER);
    //     }

    //     Util::PrintGame(game);
    // } while (!Util::CheckForWin(game, game.move_played, ((i++) % 2 == 0 ? PLAYER : COMPUTER)));

    // int moves[] = {3, 0, 2, 0, 5, 4, 3, 0};
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

    
    srand(time(NULL));

    vector<int> moveList;
    shared_ptr<Node> root = make_shared<Node>(game, PLAYER);
    root->parent = nullptr;

    do {
        if (i % 2 == 0) {
            cout << "Player's turn\n";
            cin >> last_played;
        } else {
            cout << "Computer playing...\n";
            last_played = Algorithms::MonteCarloTreeSearch(root);
        }

        for (auto child : root->children) {
            if (child->game.move_played == last_played) {
                root = child;
                break;
            }
        }
        root->parent = nullptr;
        Util::PrintGame(root->game);
        cout << last_played << "\n";
    } while (!Util::CheckForWin(root->game, root->game.move_played, ((i++) % 2 == 0 ? PLAYER : COMPUTER)) && root->game.counter != 42);
    
    
    // cin >> n;
    // for (i = 0; i < n; i++) {
    //
    //     int tmp;
    //     cin >> tmp;  // 1 = computer
    //     char move = tmp == 1 ? COMPUTER : PLAYER;
    //     char antiMove = move == COMPUTER ? PLAYER : COMPUTER;
    //
    //     int nMoves;
    //     cin >> nMoves;
    //     int col;
    //     for (int j = 0; j < nMoves; j++) {
    //         cin >> col;
    //         Util::MakeMove(col, game, j % 2 == 0 ? move : antiMove);
    //     }
    //     Util::PrintGame(game);
    //     cout << Util::UtilityFunction(game, game.move_played, nMoves % 2 == 0 ? antiMove : move);
    //     cout << "\n";
    // }

    #endif

    #ifdef ALPHA_BETA
    Game game_ab;
    game_ab.depth = 0;
    game_ab.counter = 0;

    int i_ab = 1;  // Even == PLAYER starts Odd == COMPUTER starts
    int last_played_ab;


     do {
        if (i_ab % 2 == 0) {
            cout << "Player's turn\n";
            cin >> last_played_ab;
            Util::MakeMove(last_played_ab, game_ab, PLAYER);
        } else {
            cout << "Computer playing...\n";
            last_played_ab = Algorithms::MinMaxWithAlphaBetaPruning(game_ab);
            Util::MakeMove(last_played_ab, game_ab, COMPUTER);
        }

        Util::PrintGame(game_ab);
    } while (!Util::CheckForWin(game_ab, game_ab.move_played, ((i_ab++) % 2 == 0 ? PLAYER : COMPUTER)));
    #endif

    #ifdef MINIMAX
    
    Game game_mm;
    game_mm.depth = 0;
    game_mm.counter = 0;

    int i_mm = 1;  // Even == PLAYER starts Odd == COMPUTER starts
    int last_played_mm;

    do {
        if (i_mm % 2 == 0) {
            cout << "Player's turn\n";
            cin >> last_played_mm;
            Util::MakeMove(last_played_mm, game_mm, PLAYER);
        } else {
            cout << "Computer playing...\n";
            last_played_mm = Algorithms::MinMax(game_mm);
            Util::MakeMove(last_played_mm, game_mm, COMPUTER);
        }

        Util::PrintGame(game_mm);
    } while (!Util::CheckForWin(game_mm, game_mm.move_played, ((i_mm++) % 2 == 0 ? PLAYER : COMPUTER)));
    #endif
}