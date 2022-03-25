#include "Util.h"

void Util::MakeMove(int col, Game &game, char symbol)
{
    game.board[--game.positionsPlayed[col]][col] = symbol;
    PrintGame(game);
}

void Util::PrintGame(Game &game)
{
    system("clear");
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