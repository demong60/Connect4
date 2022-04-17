#include "Util.h"

const std::string red("\033[0;31m");
const std::string red_underlined("\033[0;31;4m");
const std::string green("\033[1;32m");
const std::string green_underlined("\033[1;32;4m");
// const std::string yellow("\033[1;33m");
// const std::string cyan("\033[0;36m");
// const std::string magenta("\033[0;35m");
const std::string yellow_background_red_text("\033[1;31;103m");
const std::string yellow_background_green_text("\033[1;32;103m");


const std::string end_color("\033[0m");


pair<int, int> move_down_right = {1, 1};  // Percorrer a diagonal no sentido sudeste
pair<int, int> move_up_right = {-1, 1};   // Percorrer a diagonal no sentido nordeste
pair<int, int> move_right = {0, 1};       // Percorrer uma linha no sentido este
pair<int, int> move_down = {1, 0};        // Percorrer uma coluna no sentido sul

int Util::GetValueForSegment(pair<int, int> segment_results) {
    array<int, 3> map = {1, 10, 50};

    if (segment_results.first > 0 && segment_results.second > 0 || (segment_results.first == 0 && segment_results.second == 0))
        return 0;

    return segment_results.first > 0 ? (map[segment_results.first - 1]) : (map[segment_results.second - 1] * -1);
}

int Util::CountSegments(array<array<char, WIDTH>, HEIGHT> &board, pair<int, int> position, pair<int, int> direction) {
    int increment_y = direction.first;
    int increment_x = direction.second;
    // {X, O}
    pair<int, int> count = {0, 0};
    int result = 0;
    for (int i = 0; i < 4; ++i) {  // Initialize sliding window
        int y = position.first, x = position.second;
        if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
            return 0;
        count.first += board[y][x] == COMPUTER;
        count.second += board[y][x] == PLAYER;
        position.first += increment_y;
        position.second += increment_x;
    }

    result += GetValueForSegment(count);
    // cout << "neste momento.. " << count.first << ' ' << count.second << " with score " << result << '\n';
    while (true) {  // Continue sliding the window
        int y = position.first, x = position.second;
        if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0) {
            break;
        }
        count.first += board[y][x] == COMPUTER;
        count.second += board[y][x] == PLAYER;
        count.first -= board[y - 4 * increment_y][x - 4 * increment_x] == COMPUTER;
        count.second -= board[y - 4 * increment_y][x - 4 * increment_x] == PLAYER;

        position.first += increment_y;
        position.second += increment_x;
        result += GetValueForSegment(count);
        // cout << "\n\n";
        // cout << "neste momento.. " << count.first << ' ' << count.second << " with score " << result << '\n';
    }
    return result;
}

// Symbol == Last player
int Util::UtilityFunction(Game &game, int move) {
    char symbol = game.board[game.positions_played[move]][move];
    if (CheckForWin(game, move))
        return game.utility_value = (symbol == COMPUTER ? MAX_SCORE : -MAX_SCORE);

    // Check for draw - implement counter
    if (game.counter == 42)
        return game.utility_value = 0;

    int total = 0;  //(symbol == COMPUTER ? -16 : 16);

    // Check columns
    for (int col = 0; col < WIDTH; ++col) {
        int cur = CountSegments(game.board, {0, col}, move_down);
        total += cur;
    }

    // Check rows
    for (int row = 0; row < HEIGHT; ++row) {
        int cur = CountSegments(game.board, {row, 0}, move_right);
        total += cur;
    }

    // Primary Diagonal
    for (int row = 0; row < HEIGHT; ++row) {
        int cur = CountSegments(game.board, {row, 0}, move_down_right);
        total += cur;
    }

    for (int col = 1; col < WIDTH; ++col) {
        int cur = CountSegments(game.board, {0, col}, move_down_right);
        total += cur;
    }
    // Secondary Diagonal
    for (int row = HEIGHT - 1; row >= 0; --row) {
        int cur = CountSegments(game.board, {row, 0}, move_up_right);
        total += cur;
    }
    for (int col = 1; col < WIDTH; ++col) {
        int cur = CountSegments(game.board, {HEIGHT - 1, col}, move_up_right);
        total += cur;
    }

    return game.utility_value = total;
}

bool Util::MakeMove(int col, Game &game, char symbol) {
    if (game.positions_played[col] == 0 || col < 0 || col >= WIDTH)
        return false;

    game.board[--game.positions_played[col]][col] = symbol;

    game.move_played = col;
    game.counter++;
    game.depth++;
    return true;
}

bool Util::CheckForWin(Game &game, int col) {
    // Check horizontal
    char symbol = game.board[game.positions_played[col]][col];
    game.won_positions.push_back(make_pair(game.positions_played[col], col));

    if (symbol == ' ')
        return false;
    int sum = 1;
    int currentRow = game.positions_played[col];
    for (int colI = 1; colI <= 3 && col - colI >= 0; colI++)
        if (game.board[currentRow][col - colI] == symbol){
            game.won_positions.push_back(make_pair(currentRow, col - colI));
            sum++;
        }
        else
            break;
    for (int colI = 1; colI <= 3 && col + colI < WIDTH; colI++)
        if (game.board[currentRow][col + colI] == symbol){
            sum++;
            game.won_positions.push_back(make_pair(currentRow, col + colI));
        }
        else
            break;
    if (sum >= 4){
        return true;
    } else game.won_positions.clear();

    sum = game.board[game.positions_played[col]][col] == symbol;
    game.won_positions.push_back(make_pair(game.positions_played[col], col));

    // Check vertical
    for (int rowI = 1; rowI <= 3 && rowI < HEIGHT; rowI++)
        if (game.board[currentRow + rowI][col] == symbol){
            sum++;
            game.won_positions.push_back(make_pair(currentRow + rowI, col));
        }
        else
            break;
    if (sum >= 4){
        return true;
    } else game.won_positions.clear();

    sum = game.board[game.positions_played[col]][col] == symbol;
    game.won_positions.push_back(make_pair(game.positions_played[col], col));

    // Check main diagonal
    for (int i = 1; i <= 3 && currentRow - i >= 0 && col + i < WIDTH; i++)
        if (game.board[currentRow - i][col + i] == symbol){
            sum++;
            game.won_positions.push_back(make_pair(currentRow - i, col + i));
        }
        else
            break;
    for (int i = 1; i <= 3 && currentRow + i < HEIGHT && col - i >= 0; i++)
        if (game.board[currentRow + i][col - i] == symbol){
            sum++;
            game.won_positions.push_back(make_pair(currentRow + i, col - i));
        }
        else
            break;
    if (sum >= 4){
        return true;
    } else game.won_positions.clear();

    sum = game.board[game.positions_played[col]][col] == symbol;
    game.won_positions.push_back(make_pair(game.positions_played[col], col));

    // Check secondary diagonal
    for (int i = 1; i <= 3 && currentRow - i >= 0 && col - i >= 0; i++)
        if (game.board[currentRow - i][col - i] == symbol){
            sum++;
            game.won_positions.push_back(make_pair(currentRow - i, col - i));
        }
        else
            break;
    for (int i = 1; i <= 3 && currentRow + i < HEIGHT && col + i < WIDTH; i++)
        if (game.board[currentRow + i][col + i] == symbol){
            sum++;
            game.won_positions.push_back(make_pair(currentRow + i, col + i));
        }
        else
            break;

    if(sum < 4) game.won_positions.clear();
    return sum >= 4;
}

bool Util::IsVictoriousPiece(Game &game, int row, int col){
    for(auto position : game.won_positions){
        if(position.first == row && position.second == col) return true;
    }
    return false;
}

void Util::PrintGame(Game &game) {
    int n = system("clear");
    bool last_played_colored = false;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (col == 0)
                cout << "| ";
            if(!last_played_colored && col == game.move_played && game.board[row][col] != ' '){
                last_played_colored = true;
                if(game.board[row][col] == COMPUTER){
                    if(IsVictoriousPiece(game, row, col)){
                        cout << yellow_background_green_text << game.board[row][col] << end_color << " | ";
                    }
                    else cout << green_underlined << game.board[row][col] << end_color << " | ";
                }
                else{
                    if(IsVictoriousPiece(game, row, col)){
                        cout << yellow_background_red_text << game.board[row][col] << end_color << " | ";
                    }
                    else cout << red_underlined << game.board[row][col] << end_color << " | ";
                }
                
            } else{
                if(game.board[row][col] == COMPUTER){
                    if(IsVictoriousPiece(game, row, col)){
                        cout << yellow_background_green_text << game.board[row][col] << end_color << " | ";
                    }
                    else cout << green << game.board[row][col] << end_color << " | ";
                }
                else{
                    if(IsVictoriousPiece(game, row, col)){
                        cout << yellow_background_red_text << game.board[row][col] << end_color << " | ";
                    }
                    cout << red << game.board[row][col] << end_color << " | ";
                }
            }
        }
        cout << "\n";
    }
    for (int col = 0; col < WIDTH; col++) {
        if (col == 0)
            cout << "| ";
        cout << "- | ";
    }
    cout << '\n';
    for (int col = 0; col < WIDTH; col++) {
        if (col == 0)
            cout << "| ";
        cout << col << " | ";
    }
    cout << '\n';
}

// Returns a vector with the children of a given game
// Children are middle->out
void Util::CreateChildren(Game &game, vector<Game> &children, char symbol) {
    int middle = (WIDTH - 1) / 2;

    Game child = game;
    if (MakeMove(middle, child, symbol))
        children.push_back(child);

    for (int offset = 1; offset <= (WIDTH - 1) / 2; offset++) {
        // Right hand side
        child = game;
        if (MakeMove(middle + offset, child, symbol)) {
            children.push_back(child);
        }

        // Left hand side
        child = game;
        if (MakeMove(middle - offset, child, symbol)) {
            children.push_back(child);
        }
    }
    // for (int i = 0; i < WIDTH; i++) {
    //     Game child = game;
    //     if (MakeMove(i, child, symbol))
    //         children.push_back(child);
    // }
}

char Util::GetNextSymbol(char symbol) {
    return (symbol == COMPUTER ? PLAYER : COMPUTER);
}

double Util::CalculateUCB(Node &node) {
    if (node.visited == 0)
        return INT_MAX;

    double C = 200;
    return (node.total + C * (sqrt((double)(2 * log((double)node.parent->visited)) / (double)node.visited)));
}

shared_ptr<Node> Util::GetBestUCTChild(vector<shared_ptr<Node>> &children) {
    double max_ucb = INT_MIN;
    shared_ptr<Node> best_node;
    for (auto child : children) {
        double cur_ucb = CalculateUCB(*child);
        if (cur_ucb > max_ucb) {
            best_node = child;
            max_ucb = cur_ucb;
        }
    }

    return best_node;
}