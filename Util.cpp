#include "Util.h"

pair<int, int> move_down_right = {1, 1};  // Percorrer a diagonal no sentido sudeste
pair<int, int> move_up_right = {-1, 1};   // Percorrer a diagonal no sentido nordeste
pair<int, int> move_right = {0, 1};       // Percorrer uma linha no sentido este
pair<int, int> move_down = {1, 0};        // Percorrer uma coluna no sentido sul

pair<int, int> Util::CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> position, pair<int, int> direction) {
    int increment_y = direction.first;
    int increment_x = direction.second;
    // {X, O}
    pair<int, int> count = {0, 0};
    while (true) {
        if (position.first >= HEIGHT || position.second >= WIDTH || position.first < 0 || position.second < 0) {
            break;
        }
        count.first += board[position.first][position.second] == COMPUTER;
        count.second += board[position.first][position.second] == PLAYER;
        position.first += increment_y;
        position.second += increment_x;
    }
    return count;
}

int Util::GetValueForSegment(pair<int, int> segment_results) {
    array<int, 3> map = {1, 10, 50};

    if (segment_results.first > 0 && segment_results.second > 0)
        return 0;

    return segment_results.first > 0 ? (map[segment_results.first - 1]) : (map[segment_results.second - 1] * -1);
}

int Util::UtilityFunction(Game &game, int move, char symbol) {
    if (CheckForWin(game, move, symbol))
        return (symbol == COMPUTER) ? 512 : -512;

    // Check for draw - implement counter
    int total = (symbol == COMPUTER ? 16 : -16);

    // Check columns
    for (int col = 0; col < WIDTH; ++col) {
        pair<int, int> cur = CountSegments(game.board, {0, col}, move_down);
        total += GetValueForSegment(cur);
    }

    // Check rows
    for (int row = 0; row < HEIGHT; ++row) {
        pair<int, int> cur = CountSegments(game.board, {row, 0}, move_right);
        total += GetValueForSegment(cur);
    }

    // Primary Diagonal
    for (int row = 0; row < HEIGHT; ++row) {
        pair<int, int> cur = CountSegments(game.board, {row, 0}, move_down_right);
        total += GetValueForSegment(cur);
    }
    for (int col = 1; col < WIDTH; ++col) {
        pair<int, int> cur = CountSegments(game.board, {0, col}, move_down_right);
        total += GetValueForSegment(cur);
    }

    // Secondary Diagonal
    for (int row = HEIGHT - 1; row >= 0; --row) {
        pair<int, int> cur = CountSegments(game.board, {row, 0}, move_up_right);
        total += GetValueForSegment(cur);
    }
    for (int col = 1; col < WIDTH; ++col) {
        pair<int, int> cur = CountSegments(game.board, {HEIGHT - 1, col}, move_up_right);
        total += GetValueForSegment(cur);
    }

    return total;
}

bool Util::MakeMove(int col, Game &game, char symbol) {
    if (game.positions_played[col] == 0 || col < 0 || col >= WIDTH)
        return false;

    game.board[--game.positions_played[col]][col] = symbol;

    return true;
}

bool Util::CheckForWin(Game &game, int col, char symbol) {
    // Check horizontal
    int sum = 1;
    int currentRow = game.positions_played[col];
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

void Util::CreateChildren(Game &game, vector<Game> &children, char symbol) {
    for (int i = 0; i < WIDTH; i++) {
        if (game.positions_played[i] == 0)
            continue;
        Game child = game;
        child.depth++;
        if (MakeMove(i, child, symbol)) {
            if (child.depth == MAX_DEPTH)
                child.utility_value = Util::UtilityFunction(child, i, symbol);
            children.push_back(child);
        }
    }
}