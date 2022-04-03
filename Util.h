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
pair<int, int> CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> pos, pair<int, int> dir);
pair<int, int> count_cols(array<array<char, WIDTH>, HEIGHT> &board);
bool MakeMove(int col, Game &game, char symbol);
void PrintGame(Game &game);
void CreateChildren(Game &game, vector<Game> &children);
bool CheckForWin(Game &game, int col, char symbol);
int UtilityFunction(Game &game, int last_played, char last_played_symbol);
}  // namespace Util
