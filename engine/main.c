#include <stdio.h>
#include <ctype.h>
#include "defs.h"

enum enumPiece
{
    nWhite, // any white piece
    nBlack, // any black piece
    nPawn,
    nKnight,
    nBishop,
    nRook,
    nQueen,
    nKing
};
enum
{
    TRUE,
    FALSE
};
enum
{
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NONE
};
enum
{
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NONE
};

struct
{
    U64 pieceBB[8];
    U64 populatedBB;
    U64 key;
} BOARD;

void init()
{
    // White pieces (all pieces on ranks 1-2)
    BOARD.pieceBB[nWhite] = 0x000000000000FFFF;
    // Black pieces (all pieces on ranks 7-8)
    BOARD.pieceBB[nBlack] = 0xFFFF000000000000;
    // All pawns (rank 2 for white, rank 7 for black)
    BOARD.pieceBB[nPawn] = 0x00FF00000000FF00;
    // All knights (b1, g1, b8, g8)
    BOARD.pieceBB[nKnight] = 0x4200000000000042;
    // All bishops (c1, f1, c8, f8)
    BOARD.pieceBB[nBishop] = 0x2400000000000024;
    // All rooks (a1, h1, a8, h8)
    BOARD.pieceBB[nRook] = 0x8100000000000081;
    // All queens (d1, d8)
    BOARD.pieceBB[nQueen] = 0x0800000000000008;
    // All kings (e1, e8)
    BOARD.pieceBB[nKing] = 0x1000000000000010;

    BOARD.populatedBB = BOARD.pieceBB[nWhite] | BOARD.pieceBB[nBlack];
}

void printboard()
{
    char c = '0';
    for (int i = 63; i >= 0; i--)
    {
        U64 bit = 1ULL << i;
        if (bit & BOARD.pieceBB[nPawn])
            c = 'p';
        if (bit & BOARD.pieceBB[nBishop])
            c = 'b';
        if (bit & BOARD.pieceBB[nKnight])
            c = 'n';
        if (bit & BOARD.pieceBB[nRook])
            c = 'r';
        if (bit & BOARD.pieceBB[nQueen])
            c = 'q';
        if (bit & BOARD.pieceBB[nKing])
            c = 'k';

        if ((bit & BOARD.populatedBB) == 0)
            printf("%d", 0);
        else
            printf("%c", bit & BOARD.pieceBB[nWhite] ? toupper(c) : c);

        if (i % 8 == 0)
            printf("\n");
    }
}

int main()
{
    init();
    printboard();
    return 0;
}
