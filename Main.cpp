#include "Util.h"

int main()
{
    Game game;

    Util::MakeMove(0, game, 'O');
    Util::MakeMove(2, game, 'O');
    Util::MakeMove(2, game, 'O');

    vector<Game> children;
    Util::CreateChildren(game, children);

    Util::PrintGame(game);
    cout << "\n\n\n";
    for (Game child : children)
    {
        Util::PrintGame(child);
        cout << "\n\n\n";
    }

    Util::PrintGame(game);
}