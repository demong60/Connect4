#pragma once
#include <bits/stdc++.h>

using namespace std;
#define WIDTH 7
#define HEIGHT 6
#define COMPUTER 'X'
#define PLAYER 'O'

#define MAX_DEPTH 5

#include "Game.h"
#include "Algorithms.h"

namespace Util {

pair<int, int> CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> pos, pair<int, int> dir);
bool MakeMove(int col, Game &game, char symbol);
void PrintGame(Game &game);
void CreateChildren(Game &game, vector<Game> &children, char symbol);
bool CheckForWin(Game &game, int col, char symbol);
int UtilityFunction(Game &game, int move, char symbol);
int GetValueForSegment(pair<int, int> segment_results);
}  // namespace Util
