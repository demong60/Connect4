#include "Util.h"

int Algorithms::MinMax(Game &game) {
    if (game.depth == 0)
        return (WIDTH - 1) / 2;
    game.depth = 0;
    return MaxValue(game).second;
}

pair<int, int> Algorithms::MaxValue(Game &game) {
    if (game.depth == MAX_DEPTH)
        return {Util::UtilityFunction(game, game.move_played, PLAYER), game.move_played};  //+ verificar se o jogo acabou: não sei qual é melhor maneira de verificar isto
    if (Util::CheckForWin(game, game.move_played, PLAYER)) return {-512, game.move_played};
    if (Util::CheckForWin(game, game.move_played, COMPUTER)) return {512, game.move_played};
    if (game.counter == 42) return {0, game.move_played};

    pair<int, int> value = {INT_MIN, -1};
    vector<Game> children;
    Util::CreateChildren(game, children, COMPUTER);
    for (Game child : children) {
        // Util::PrintGame(child);

        pair<int, int> cur = MinValue(child);

        if (cur.first > value.first) {
            value = cur;
        }
    }
    return value;
}

pair<int, int> Algorithms::MinValue(Game &game) {
    if (game.depth == MAX_DEPTH)
        return {Util::UtilityFunction(game, game.move_played, COMPUTER), game.move_played};  //+ verificar se o jogo acabou: não sei qual é melhor maneira de verificar isto

    if (Util::CheckForWin(game, game.move_played, COMPUTER)) return {512, game.move_played};
    if (Util::CheckForWin(game, game.move_played, PLAYER)) return {-512, game.move_played};
    if (game.counter == 42) return {0, game.move_played};

    pair<int, int> value = {INT_MAX, -1};
    vector<Game> children;
    Util::CreateChildren(game, children, PLAYER);
    for (Game child : children) {
        // Util::PrintGame(child);
        pair<int, int> cur = MaxValue(child);
        if (cur.first < value.first) {
            value = cur;
        }
    }
    return value;
}
