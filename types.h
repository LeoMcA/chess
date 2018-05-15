#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

typedef uint64_t bitboard;

typedef enum { none, king, queen, rook, bishop, knight, pawn } piece;
typedef enum { white, black } color;
typedef struct {
  color color : 1;
  piece piece : 3;
} square;
typedef square arrayboard[8][8];

void print_binary (bitboard b);
void print_arrayboard (arrayboard *a);
void bitboards_to_arrayboard (arrayboard *a);
bitboard *piece_to_bitboard (piece piece, color color);
void update_boards (arrayboard *a, int start_x, int start_y, int end_x, int end_y);
int valid_move (arrayboard *a, int start_x, int start_y, int end_x, int end_y);

#define KING    (bitboard) 1           << 3
#define QUEEN   (bitboard) 1           << 4
#define ROOKS   (bitboard)(1 << 7 | 1)
#define BISHOPS (bitboard)(1 << 3 | 1) << 2
#define KNIGHTS (bitboard)(1 << 5 | 1) << 1
#define PAWNS   (bitboard) 255         << 8

extern bitboard white_king;
extern bitboard white_queen;
extern bitboard white_rooks;
extern bitboard white_bishops;
extern bitboard white_knights;
extern bitboard white_pawns;

extern bitboard black_king;
extern bitboard black_queen;
extern bitboard black_rooks;
extern bitboard black_bishops;
extern bitboard black_knights;
extern bitboard black_pawns;

extern bitboard *bitboards[12];

#endif
