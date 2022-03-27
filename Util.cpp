#include "Util.h"

bool Util::MakeMove(int col, Game &game, char symbol)
{
    if (game.positionsPlayed[col] == 0 || col < 0 || col >= WIDTH)
        return false;
    game.board[--game.positionsPlayed[col]][col] = symbol;
    PrintGame(game);
    return true;
}

bool Util::CheckForWin(Game &game, int col, char symbol)
{
    // Check horizontal
    int sum = 1;
    int currentRow = game.positionsPlayed[col];
    for (int colI = 1; colI <= 3 && col - colI >= 0; colI++)
        if (game.board[currentRow][col - colI] == symbol)
            sum++;
        else
            break;
    for (int colI = 1; colI <= 3 && col + colI < WIDTH; colI++)
        if (game.board[currentRow][col + colI] == symbol)
            sum++;
        else
            break;
    if (sum == 4)
        return true;

    sum = 1;
    // Check vertical
    for (int rowI = 1; rowI <= 3 && rowI < HEIGHT; rowI++)
        if (game.board[currentRow + rowI][col] == symbol)
            sum++;
        else
            break;
    if (sum == 4)
        return true;

    sum = 1;
    // Check main diagonal
    for (int i = 1; i <= 3 && currentRow - i >= 0 && col + i < WIDTH; i++)
        if (game.board[currentRow - i][col + i] == symbol)
            sum++;
        else
            break;
    for (int i = 1; i <= 3 && currentRow + i < HEIGHT && col - i >= 0; i++)
        if (game.board[currentRow + i][col - i] == symbol)
            sum++;
        else
            break;
    if (sum == 4)
        return true;

    sum = 1;
    // Check secondary diagonal
    for (int i = 1; i <= 3 && currentRow - i >= 0 && col - i >= 0; i++)
        if (game.board[currentRow - i][col - i] == symbol)
            sum++;
        else
            break;
    for (int i = 1; i <= 3 && currentRow + i < HEIGHT && col + i < WIDTH; i++)
        if (game.board[currentRow + i][col + i] == symbol)
            sum++;
        else
            break;

    return sum == 4;
}

void Util::PrintGame(Game &game)
{
    int n = system("clear");
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            if (col == 0)
                cout << "| ";
            cout << game.board[row][col] << " | ";
        }
        cout << "\n";
    }
}

void Util::CreateChildren(Game &game, vector<Game> &children)
{
    for (int i = 0; i < WIDTH; i++)
    {
        if (game.positionsPlayed[i] == 0)
            continue;
        Game child = game;
        MakeMove(i, child, 'X');
        children.push_back(child);
    }
}