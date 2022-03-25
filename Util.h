#pragma once
#include <bits/stdc++.h>

using namespace std;
#define WIDTH 7
#define HEIGHT 6

#include "Game.h"
#include "Algorithms.h"

namespace Util
{
    void MakeMove(int col, Game &game, char symbol);
    void PrintGame(Game &game);
    void CreateChildren(Game &game, vector<Game> &children);
}
