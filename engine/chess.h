#include <bitset>
#include <string>

enum Squares {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
};
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum Type{ nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing };
enum Flags{ wtm, benp, wenp, wk1, wk2, bk1, bk2, ch };

struct Move{
    u_int8_t origin;
    u_int8_t destination;
};

struct Piece{
    u_int8_t Piece;
    u_int8_t Type;
};

class Chessboard{
    private:
        u_int64_t bitboards[8];
        u_int64_t poskey;
        u_int16_t ply;
        std::bitset<8> flags;
    public:
        u_int64_t popBB;
        Chessboard();
        void initBB();
        void makeMove(Move move);
        bool validateMove(Move move);
        u_int64_t getBB(Piece piece);
        std::string getFEN();
};
