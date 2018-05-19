#include <locale.h>

#include "types.h"
#include "gui.h"

int main () {
  setlocale(LC_ALL, "");

  bitboards_to_arrayboard();
  setup_window();
  setup_board();
  draw_board();
  setup_mouse();
  getch();
  endwin();

  return 0;
}
