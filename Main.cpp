#include "Util.h"

int OlaMarco(){
    return 5;
}

int main() {
    // cout << "Cross starts: \n";
    // Game game;
    // int lastPlayed;
    // cin >> lastPlayed;
    // Util::MakeMove(lastPlayed, game, COMPUTER);

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

    srand(time(NULL));
    array<array<char, WIDTH>, HEIGHT> board;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            board[i][j] = (rand() % 2 == 0 ? COMPUTER : PLAYER);
        }
    }

    for (auto elem : board) {
        for (auto x : elem) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}