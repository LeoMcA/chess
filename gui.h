#include <ncurses.h>

#include "types.h"

void setup_window ();
void draw_board_with_highlight (arrayboard *a, int x_highlight, int y_highlight);
void draw_arrayboard (arrayboard *a);
void highlight_board (arrayboard *a, int x, int y);
void setup_mouse (arrayboard *a);
void mouse_clicked (arrayboard *a, MEVENT *e);
