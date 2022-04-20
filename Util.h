#pragma once
#include <bits/stdc++.h>

using namespace std;
#define WIDTH 7
#define HEIGHT 6
#define COMPUTER 'X'
#define PLAYER 'O'

#define MAX_DEPTH 7
#define MAX_DEPTH_AB 10
#define MAX_SCORE 10000

#include "Game.h"
#include "Algorithms.h"
#include "Node.h"

namespace Util {
extern int node_count;
/**
 * @brief Counts the number of each type of piece in each 4-piece segment in a given direction, for example, all the pieces in each segment in the first row.
 *
 * @param board Board to be used for counting
 * @param pos Position to start counting
 * @param dir Direction to be taken when counting
 * @return int Value for all the segments in the searched space of the board
 */
int CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> pos, pair<int, int> dir);

/**
 * @brief Tries to make a move on the board
 *
 * @param col Column to place the piece on
 * @param game Game to be updated
 * @param symbol Symbol that is currently playing, PLAYER or COMPUTER
 * @return true If the move was sucessfully made
 * @return false If col represents an ilegal move
 */
bool MakeMove(int col, Game &game, char symbol);

/**
 * @brief Prints the current board of a game
 * 
 * @param game Game to print
 */
void PrintGame(Game &game);

/**
 * @brief Prints a victorious game, where some player has won, and the winning position highlighted
 * 
 * @param game Game to print
 */
void PrintVictoriousGame(Game &game);

/**
 * @brief Creates the children for a game, starting from the middle and working outwards
 * 
 * @param game Game to be used to create it's children
 * @param children Vector that will store the children of the game
 * @param symbol Symbol to be used when making the moves, PLAYER or COMPUTER
 */
void CreateChildren(Game &game, vector<Game> &children, char symbol);

/**
 * @brief Checks for a win by any player in the last made move
 * 
 * @param game Game to be checked
 * @param col Column where the last move was made
 * @return true If there was a win
 * @return false If there isn't a win
 */
bool CheckForWin(Game &game, int col);

/**
 * @brief Checks if a piece is victorious, so that it is highlighted in the final print.
 * 
 * @param won_positions Positions that are won
 * @param row Row of the piece to check
 * @param col Col of the piece to check
 * @return true If it is a victorious piece
 * @return false 
 */
bool IsVictoriousPiece(vector<pair<int, int>> &won_positions, int row, int col);

/**
 * @brief Gets the segment that won the game
 * 
 * @param game 
 * @param col 
 * @return vector<pair<int, int>> 
 */
vector<pair<int, int>> GetWinSegment(Game &game, int col);

/**
 * @brief Returns the utility value for a given game
 * 
 * @param game Game to calculate the utility value for
 * @param move Last made move
 * @return int Value for the game
 */
int UtilityFunction(Game &game, int move);

/**
 * @brief Get the value for a given segment
 * 
 * @param segment_results Pair with the ammount of each type of piece in the segment
 * @return int Value fo the segment
 */
int GetValueForSegment(pair<int, int> segment_results);

/**
 * @brief Given a symbol like PLAYER, returns COMPUTER
 * 
 * @param symbol The current symbol
 * @return char The opposite symbol
 */
char GetNextSymbol(char symbol);

/**
 * @brief Calculated the UCB function for a given node.
 * 
 * @param node Node to calculate the UCB
 * @return double UCB of the given node.
 */
double CalculateUCB(Node &node);

/**
 * @brief Returns a shared_ptr<Node> to the child with the best UCT value.
 * 
 * @param children Children of the Node.
 * @return shared_ptr<Node> 
 */
shared_ptr<Node> GetBestUCTChild(vector<shared_ptr<Node>> &children);
}  // namespace Util
