#include <stdio.h>
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
}

int main()
{
    init();
    U64 board = BOARD.pieceBB[nWhite] | BOARD.pieceBB[nBlack];
    printf("%c", '\n');

    //print locations of all pieces
    for (int i = 0; i < 64; i++)
    {
        printf("%d", (1ULL << i) & board ? 1 : 0);
        if ((i + 1) % 8 == 0 && i != 0)
            printf("%c", '\n');
    }
    printf("%c", '\n');

    //print white pawns
    for (int i = 63; i >= 0; i--)
    {
        printf("%c", (1ULL << i) & BOARD.pieceBB[nPawn] & BOARD.pieceBB[nWhite] ? 'P' : '0');
        if (i%8 == 0)
            printf("%c", '\n');
    }
    printf("%c", '\n');

    //print black pawns
    for (int i = 63; i >= 0; i--)
    {
        printf("%c", (1ULL << i) & BOARD.pieceBB[nPawn] & BOARD.pieceBB[nBlack] ? 'p' : '0');
        if (i%8 == 0)
            printf("%c", '\n');
    }
    printf("%c", '\n');

    
    return 0;
}
