#include "defs.h"
#include <ctype.h>
#include <stdio.h>

// clang-format off
enum enumPiece { nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing };
enum { TRUE, FALSE };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { WTM = 1, ENP = 2, WC = 4, BC = 8 } FLAGS;
enum enumSquare {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
};
// clang-format on

struct {
  U64 pieceBB[8];
  U64 populatedBB;
  U64 key;
  char flags;
} BOARD;

struct {
  U64 uboards[8];
  U64 key;
} UNDO;

void init() {
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

// eventually use bitmasks to validate moves
void makeMove(int start, int des) {
  U64 sbit = 1ULL << start;
  U64 dbit = 1ULL << des;
  for (int i = 0; i < 8; i++) {
    if (sbit & BOARD.pieceBB[i]) {
      BOARD.pieceBB[i] ^= sbit;
      BOARD.pieceBB[i] |= dbit;
    }
  }
  BOARD.populatedBB ^= sbit;
  BOARD.populatedBB |= dbit;
  // Change turn
  if (BOARD.flags % WTM == 0)
    BOARD.flags -= WTM;
  BOARD.flags += WTM;
}

void getFEN() {
  char c;
  int count = 0;

  for (int rank = RANK_8; rank >= RANK_1; rank--) {
    count = 0;
    if (rank < RANK_8)
      printf("%c", '/');
    for (int file = FILE_A; file <= FILE_H; file++) {
      int square = file + (rank * 8);
      U64 bit = 1ULL << square;
      // Increment count for empty spaces
      if (!(bit & BOARD.populatedBB)) {
        count++;
      } else {
        if (count > 0) {
          printf("%d", count);
          count = 0;
        }
        // Check piece type
        if (bit & BOARD.pieceBB[nPawn])
          c = 'p';
        else if (bit & BOARD.pieceBB[nBishop])
          c = 'b';
        else if (bit & BOARD.pieceBB[nKnight])
          c = 'n';
        else if (bit & BOARD.pieceBB[nRook])
          c = 'r';
        else if (bit & BOARD.pieceBB[nQueen])
          c = 'q';
        else if (bit & BOARD.pieceBB[nKing])
          c = 'k';
        // Print piece
        printf("%c", bit & BOARD.pieceBB[nWhite] ? toupper(c) : c);
      }
    }
    if (count > 0)
      printf("%d", count);
  }
}

int main() {
  getFEN();
  init();
  getFEN();
  makeMove(f2, f4);
  printf("\n");
  getFEN();
  return 0;
}