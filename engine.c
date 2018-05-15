#include <locale.h>

#include "types.h"
#include "gui.h"

int main () {
  setlocale(LC_ALL, "");

  arrayboard a = {};
  bitboards_to_arrayboard(&a);
  // print_arrayboard(&a);

  setup_window();
  draw_arrayboard(&a);
  setup_mouse(&a);
  getch();
  endwin();

  return 0;
}
