#include <locale.h>

#include "types.h"
#include "gui.h"

int main () {
  setlocale(LC_ALL, "");

  arrayboard a = {};
  bitboards_to_arrayboard(&a);
  print_arrayboard(&a);

  return 0;
}
