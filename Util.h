#pragma once
#include <bits/stdc++.h>

using namespace std;
#define WIDTH 7
#define HEIGHT 6
#define COMPUTER 'X'
#define PLAYER 'O'

#define MAX_DEPTH 2
#define MAX_SCORE 512

#include "Game.h"
#include "Algorithms.h"
#include "Node.h"

namespace Util {

int CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> pos, pair<int, int> dir);
bool MakeMove(int col, Game &game, char symbol);
void PrintGame(Game &game);
void CreateChildren(Game &game, vector<Game> &children, char symbol);
bool CheckForWin(Game &game, int col, char symbol);
int UtilityFunction(Game &game, int move, char symbol);
int GetValueForSegment(pair<int, int> segment_results);
char GetNextSymbol(char symbol);
double CalculateUCB(Node &node);
shared_ptr<Node> GetBestUCTChild(vector<shared_ptr<Node>> &children);
}  // namespace Util
