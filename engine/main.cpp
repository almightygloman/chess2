#include "chess.h"
#include "iostream"

int main(int argc, char *argv[]){
    
    Chessboard board = Chessboard();
    board.initBB();
    std::cout<<board.getFEN();
    std::cout<<'\n';

    Move move = {
        f2,f4
    };
    board.makeMove(move);
    std::cout<<board.getFEN();
    std::cout<<'\n';

    return 0;
}