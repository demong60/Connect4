#pragma once
#include "Util.h"

class Game {
   public:
    array<array<char, WIDTH>, HEIGHT> board;
    array<int, WIDTH> positions_played;
    vector<pair<int, int>> won_positions;
    int utility_value;
    int depth;
    int counter;
    int move_played;
    Game();
};