#include "Util.h"

pair<int, int> down_right = {1, 1};  // Percorrer a diagonal no sentido sudeste
pair<int, int> up_right = {-1, 1};   // Percorrer a diagonal no sentido nordeste
pair<int, int> right = {0, 1};       // Percorrer uma linha no sentido este
pair<int, int> down = {1, 0};        // Percorrer uma coluna no sentido sul

pair<int, int> Util::CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> pos, pair<int, int> dir) {
    int incy = dir.first;
    int incx = dir.second;
    pair<int, int> cnt = {0, 0};
    while (true) {
        if (pos.first >= HEIGHT || pos.second >= WIDTH || pos.first < 0 || pos.second < 0) {
            break;
        }
        cnt.first += board[pos.first][pos.second] == CROSS;
        cnt.second += board[pos.first][pos.second] == CIRCLE;
        pos.first += incy;
        pos.second += incx;
    }
    return cnt;
}

pair<int, int> Util::count_cols(array<array<char, WIDTH>, HEIGHT> &board) {
    pair<int, int> ans = {0, 0};
    for (int i = 0; i < WIDTH; ++i) {
        pair<int, int> cur = CountSegments(board, make_pair(0, i), down);
        ans.first += cur.first;
        ans.second += cur.second;
    }
    return ans;
}

bool Util::MakeMove(int col, Game &game, char symbol) {
    if (game.positionsPlayed[col] == 0 || col < 0 || col >= WIDTH)
        return false;
    game.board[--game.positionsPlayed[col]][col] = symbol;
    PrintGame(game);
    return true;
}

bool Util::CheckForWin(Game &game, int col, char symbol) {
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

void Util::PrintGame(Game &game) {
    int n = system("clear");
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (col == 0)
                cout << "| ";
            cout << game.board[row][col] << " | ";
        }
        cout << "\n";
    }
}

void Util::CreateChildren(Game &game, vector<Game> &children) {
    for (int i = 0; i < WIDTH; i++) {
        if (game.positionsPlayed[i] == 0)
            continue;
        Game child = game;
        MakeMove(i, child, CROSS);

        // Check if child.depth >= MAX_DEPTH
        // if it is callUtilityFunction on child
        children.push_back(child);
    }
}

int Util::UtilityFunction(Game &game, int last_played, char last_played_symbol) {
    int game_utility = 0;
    if (CheckForWin(game, last_played, last_played_symbol))
        if (last_played_symbol == CIRCLE)
            return -512;
        else
            return 512;
    else
        return 0;
}