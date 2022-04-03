#pragma once
#include "Util.h"

class Game {
   public:
    array<array<char, WIDTH>, HEIGHT> board;
    array<int, WIDTH> positionsPlayed;
    Game();
};