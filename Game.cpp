#include "Util.h"

array<array<char, WIDTH>, HEIGHT> board;
array<int, WIDTH> positionsPlayed;
Game::Game() {
    for (int row = 0; row < HEIGHT; row++)
        board[row].fill(' ');

    positionsPlayed.fill(HEIGHT);
}