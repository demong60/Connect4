#pragma once
#include <bits/stdc++.h>

using namespace std;
#define WIDTH 7
#define HEIGHT 6
#define CROSS 'X'
#define CIRCLE 'O'

#include "Algorithms.h"
#include "Game.h"

namespace Util {
bool MakeMove(int col, Game &game, char symbol);
void PrintGame(Game &game);
void CreateChildren(Game &game, vector<Game> &children);
bool CheckForWin(Game &game, int col, char symbol);
int UtilityFunction(Game &game, char symbol);
}  // Namespace Util
