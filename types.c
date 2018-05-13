#include "types.h"

#include <stdio.h>
#include <limits.h>

bitboard white_king    = KING    << 8 * 7;
bitboard white_queen   = QUEEN   << 8 * 7;
bitboard white_rooks   = ROOKS   << 8 * 7;
bitboard white_bishops = BISHOPS << 8 * 7;
bitboard white_knights = KNIGHTS << 8 * 7;
bitboard white_pawns   = PAWNS   << 8 * 5;

bitboard black_king    = KING;
bitboard black_queen   = QUEEN;
bitboard black_rooks   = ROOKS;
bitboard black_bishops = BISHOPS;
bitboard black_knights = KNIGHTS;
bitboard black_pawns   = PAWNS;

bitboard *bitboards[12] = {
  &white_king, &white_queen, &white_rooks, &white_bishops, &white_knights, &white_pawns,
  &black_king, &black_queen, &black_rooks, &black_bishops, &black_knights, &black_pawns
};

void print_bitboard (bitboard b) {
  // https://stackoverflow.com/a/35926790
  int i = CHAR_BIT * sizeof(bitboard);
  while (i--) {
    putchar('0' + ((b >> i) & 1));
  }
  putchar('\n');
}

void print_arrayboard (arrayboard *a) {
  printf("  a b c d e f g h\n");
  for (int y = 7; y >= 0; y--) {
    printf("%d ", y + 1);
    for (int x = 0; x < 8; x++) {
      square s = (*a)[y][x];
      if (s.piece != none) {
        printf("\xe2\x99");
        putchar('\x93' + s.piece + s.color * 6);
        putchar(' ');
      } else {
        printf("  ");
      }
    }
    printf("%d \n", y + 1);
  }
  printf("  a b c d e f g h\n");
}

void bitboards_to_arrayboard (arrayboard *a) {
  for (color color = 0; color < 2; color++) {
    for (piece piece = 1; piece < 7; piece++) {
      bitboard b = *bitboards[piece - 1 + color * 6];
      int x = 7;
      int y = 7;
      while (b != 0) {
        if (b & 1) {
          (*a)[y][x] = (square){ color, piece };
        }
        b >>= 1;
        if (x == 0) {
          x = 7;
          y--;
        } else {
          x--;
        }
      }
    }
  }
}
