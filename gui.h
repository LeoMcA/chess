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
void draw_board ();
void setup_mouse ();
void mouse_clicked (MEVENT *e);
