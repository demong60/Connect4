#include "Util.h"

// void print(Game &game){
//   for(auto elem : game.board){
//     for(auto x : elem){
//       cout << x << ' ';
//     } cout << '\n';
//   }
// }
int main() {
    int i = 1;  // Even == PLAYER starts Odd == COMPUTER starts
    int last_played;
    Game game;
    game.depth = 0;
    game.counter = 0;
    game.move_played = 3;

    do {
        if (i % 2 == 0) {
            cout << "Player's turn\n";
            cin >> last_played;
            Util::MakeMove(last_played, game, PLAYER);
        } else {
            cout << "Computer playing...\n";
            last_played = Algorithms::MinMax(game);
            Util::MakeMove(last_played, game, COMPUTER);
        }

        Util::PrintGame(game);
    } while (!Util::CheckForWin(game, game.move_played, ((i++) % 2 == 0 ? PLAYER : COMPUTER)));

    // int n;
    // cin >> n;
    // for (int i = 0; i < n; i++) {

    //     int tmp;
    //     cin >> tmp;  // 1 = computer
    //     char move = tmp == 1 ? COMPUTER : PLAYER;
    //     char antiMove = move == COMPUTER ? PLAYER : COMPUTER;

    //     int nMoves;
    //     cin >> nMoves;
    //     int col;
    //     for (int j = 0; j < nMoves; j++) {
    //         cin >> col;
    //         Util::MakeMove(col, game, j % 2 == 0 ? move : antiMove);
    //     }
    //     // Util::PrintGame(game);
    //     cout << Util::UtilityFunction(game, game.move_played, nMoves % 2 == 0 ? antiMove : move);
    //     cout << "\n";
    // }
}
