#include <locale.h>

#include "types.h"
#include "gui.h"

int main () {
  setlocale(LC_ALL, "");

  bitboards_to_arrayboard();
  setup_window();
  draw_arrayboard();
  setup_mouse();
  getch();
  endwin();

  return 0;
}
