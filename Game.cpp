#include "Util.h"

array<array<char, WIDTH>, HEIGHT> board;
array<int, WIDTH> positions_played;
int utility_value;
int depth;
int counter;
Game::Game() {
    for (int row = 0; row < HEIGHT; row++)
        board[row].fill(' ');

    positions_played.fill(HEIGHT);
}