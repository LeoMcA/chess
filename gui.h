#include <ncurses.h>

#include "types.h"

typedef struct {
  color square_color;
  piece piece;
  color piece_color;
  unsigned int highlight;
} guisquare_t;
typedef guisquare_t guiboard_t[8][8];

void setup_window ();
void setup_board ();
void arrayboard_to_guiboard ();
void draw_board_with_highlight (int x_highlight, int y_highlight);
void draw_board ();
void highlight_board (int x, int y);
void setup_mouse ();
void mouse_clicked (MEVENT *e);
