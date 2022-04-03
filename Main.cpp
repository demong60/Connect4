#include "Util.h"

int main() {
    Game game;

    Util::MakeMove(0, game, CIRCLE);
    Util::MakeMove(1, game, CROSS);
    Util::MakeMove(2, game, CIRCLE);
    Util::MakeMove(2, game, CIRCLE);

    vector<Game> children;
    Util::CreateChildren(game, children);

    Util::PrintGame(game);
    cout << "\n\n\n";

    for (Game child : children) {
        Util::PrintGame(child);
        cout << "\n\n\n";
    }

    Util::PrintGame(game);
}