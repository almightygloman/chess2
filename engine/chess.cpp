#include "chess.h"
#include <iostream>

Chessboard::Chessboard()
{
    ply = 0;
    flags[wtm] = 1;
}

void Chessboard::initBB()
{
    // white pieces (all pieces on ranks 1-2)
    bitboards[nWhite] = 0x000000000000FFFF;
    // black pieces (all pieces on ranks 7-8)
    bitboards[nBlack] = 0xFFFF000000000000;
    // pawns (rank 2 for white, rank 7 for black)
    bitboards[nPawn] = 0x00FF00000000FF00;
    // knights (b1, g1, b8, g8)
    bitboards[nKnight] = 0x4200000000000042;
    // bishops (c1, f1, c8, f8)
    bitboards[nBishop] = 0x2400000000000024;
    // rooks (a1, h1, a8, h8)
    bitboards[nRook] = 0x8100000000000081;
    // queens (d1, d8)
    bitboards[nQueen] = 0x0800000000000008;
    // kings (e1, e8)
    bitboards[nKing] = 0x1000000000000010;

    popBB = bitboards[nWhite] | bitboards[nBlack];
}

void Chessboard::makeMove(Move move)
{
    // bit masks to scan and update bitboards
    u_int64_t sbit = 1ULL << move.origin;
    u_int64_t dbit = 1ULL << move.destination;
    for (int i = 0; i < 8; i++)
    {
        if (sbit & bitboards[i])
        {
            bitboards[i] ^= sbit;
            bitboards[i] |= dbit;
        }
    }
    popBB ^= sbit;
    popBB |= dbit;

    // change turn
    if (flags[wtm] == 0)
        flags[wtm] = 1;
    else
        flags[wtm] = 0;

    // increment ply
    ply++;
}

bool Chessboard::validateMove(Move move)
{
    if (flags[wtm] == 1)
        return 1ULL << move.origin & bitboards[nWhite];

    return 1ULL << move.origin & bitboards[nWhite];
}

std::string Chessboard::getFEN()
{
    std::string fen;
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        int count = 0;
        for (int file = FILE_A; file <= FILE_H; file++) {
            int square = file + rank * 8;
            u_int64_t bit = 1ULL << square;
            if (!(bit & popBB)) {
                count++;
            } else {
                if (count > 0) {
                    fen += std::to_string(count);
                    count = 0;
                }
                // get piece at square
                char pieceChar = '?';
                if (bit & bitboards[nPawn]) pieceChar = 'P';
                else if (bit & bitboards[nKnight]) pieceChar = 'N';
                else if (bit & bitboards[nBishop]) pieceChar = 'B';
                else if (bit & bitboards[nRook]) pieceChar = 'R';
                else if (bit & bitboards[nQueen]) pieceChar = 'Q';
                else if (bit & bitboards[nKing]) pieceChar = 'K';

                // Check color
                if (bit & bitboards[nBlack])
                    pieceChar = std::tolower(pieceChar);

                fen += pieceChar;
            }
        }
        if (count > 0) fen += std::to_string(count);
        if (rank > RANK_1) fen += '/';
    }

    // append ply
    fen += flags[wtm] ? " w " : " b ";

    // worry abt the rest later
    fen += "- - 0 ";
    fen += std::to_string(ply / 2); // fullmove number
    return fen;
}
