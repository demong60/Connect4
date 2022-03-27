#include "Util.h"

int main()
{
    cout << "Cross starts: \n";
    Game game;
    int lastPlayed;
    cin >> lastPlayed;
    Util::MakeMove(lastPlayed, game, CROSS);

    int i = 0;
    while (!Util::CheckForWin(game, lastPlayed, CROSS))
    {
        i++;
        cin >> lastPlayed;
        while (!Util::MakeMove(lastPlayed, game, i % 2 == 0 ? CROSS : CIRCLE))
        {
            cin >> lastPlayed;
        }
    }
    cout << (lastPlayed % 2 == 1 ? CROSS : CIRCLE) << " WINS!";
}