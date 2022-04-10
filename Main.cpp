#include "Util.h"

// void print(Game &game){
//   for(auto elem : game.board){
//     for(auto x : elem){
//       cout << x << ' ';
//     } cout << '\n';
//   }
// }

int main() {
    Game game;
    game.depth = 0;
    game.counter = 0;

    int i = 1;  // Even == PLAYER starts Odd == COMPUTER starts
    int last_played;

    Util::PrintGame(game);

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

    // Util::MakeMove(2, game, COMPUTER);
    // Util::PrintGame(game);

    // cout << "ver: " << Util::CheckForWin(game, game.move_played, COMPUTER) << '\n';
    // cout << "counter:" << game.counter << '\n';
    // cout << "depth:" << game.depth << '\n';
    // cout << "last_played: " << game.move_played << '\n';

    // int i = 0;
    // while (!Util::CheckForWin(game, lastPlayed, COMPUTER))
    // {
    //     i++;
    //     cin >> lastPlayed;
    //     while (!Util::MakeMove(lastPlayed, game, i % 2 == 0 ? COMPUTER : PLAYER))
    //     {
    //         cin >> lastPlayed;
    //     }
    // }
    // cout << (lastPlayed % 2 == 1 ? COMPUTER : PLAYER) << " WINS!";

    // srand(time(NULL));
    // array<array<char, WIDTH>, HEIGHT> board;
    // for (int i = 0; i < HEIGHT; ++i) {
    // for (int j = 0; j < WIDTH; ++j) {
    // board[i][j] = (rand() % 2 == 0 ? COMPUTER : PLAYER);
    // }
    // }
    //
    // for (auto elem : board) {
    // for (auto x : elem) {
    // cout << x << ' ';
    // }
    // cout << '\n';
    // }

    // cout << MinMax(game) << '\n';
}
