#include "Util.h"

int main()
{
    // cout << "Cross starts: \n";
    // Game game;
    // int lastPlayed;
    // cin >> lastPlayed;
    // Util::MakeMove(lastPlayed, game, CROSS);

    // int i = 0;
    // while (!Util::CheckForWin(game, lastPlayed, CROSS))
    // {
    //     i++;
    //     cin >> lastPlayed;
    //     while (!Util::MakeMove(lastPlayed, game, i % 2 == 0 ? CROSS : CIRCLE))
    //     {
    //         cin >> lastPlayed;
    //     }
    // }
    // cout << (lastPlayed % 2 == 1 ? CROSS : CIRCLE) << " WINS!";

    srand(time(NULL));
    array<array<char, WIDTH>, HEIGHT> board;
    for(int i=0; i<HEIGHT; ++i){
        for(int j=0; j<WIDTH; ++j){
            board[i][j] = (rand()%2 == 0 ? CROSS : CIRCLE);
        }
    }

    for(auto elem : board){
        for(auto x : elem){
            cout << x << ' ';
        } cout << '\n';
    }

    // 1 0 -> Ver linha a linha

    // for(int i=0; i<HEIGHT; ++i){
    //     pair<int, int> cur_res = Util::CountSegments(board, {i, 0}, 0, 1);
    //     cout << "Linha " << i << ": " << cur_res.first << ' ' << cur_res.second << '\n';
    // }

    

    // pair<int, int> res = Util::CountSegments(board, {0, 1}, down_right); // Função principal que conta quantos X's e O's estão na linha / coluna / diagonal da posição entre aspas 
    pair<int, int> res_cols = Util::count_cols(board);
    cout << "nas colunas: " << res_cols.first << ' ' << res_cols.second << '\n';

}