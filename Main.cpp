#include "Util.h"

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

    Game game;
    Util::MakeMove(0, game, COMPUTER);
    Util::MakeMove(0, game, PLAYER);
    // Util::MakeMove(1, game, COMPUTER);
    // Util::MakeMove(1, game, PLAYER);
    // Util::MakeMove(2, game, COMPUTER);
    // Util::MakeMove(2, game, PLAYER);
    Util::PrintGame(game);
    int ans = Util::UtilityFunction(game, 2, PLAYER);
    cout << "tem " << ans << " de pontuação.." << '\n';
    
    // srand(time(NULL));
    // array<array<char, WIDTH>, HEIGHT> board;
    // for (int i = 0; i < HEIGHT; ++i) {
    //     for (int j = 0; j < WIDTH; ++j) {
    //         board[i][j] = (rand() % 2 == 0 ? COMPUTER : PLAYER);
    //     }
    // }

    // for (auto elem : board) {
    //     for (auto x : elem) {
    //         cout << x << ' ';
    //     }
    //     cout << '\n';
    // }
    // Game g;
    // g.board = board;

    // int ans = Util::UtilityFunction(g, 0, COMPUTER);
    // cout << "tem " << ans << " de pontuação.." << '\n';
}