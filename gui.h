#include <ncurses.h>

#include "types.h"

void setup_window ();
void draw_board_with_highlight (int x_highlight, int y_highlight);
void draw_arrayboard ();
void highlight_board (int x, int y);
void setup_mouse ();
void mouse_clicked (MEVENT *e);
