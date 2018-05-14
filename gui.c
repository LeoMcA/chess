#include "gui.h"

void setup_window () {
  initscr();
  clear();
  noecho();
  cbreak();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
}

void draw_arrayboard (arrayboard *a) {
  printw("    a  b  c  d  e  f  g  h    \n");
  for (int y = 7; y >= 0; y--) {
    printw(" %d ", y + 1);
    for (int x = 0; x < 8; x++) {
      color sc = y % 2 == x % 2;
      if (sc) {
        attron(COLOR_PAIR(2));
      } else {
        attron(COLOR_PAIR(1));
      }
      square s = (*a)[y][x];
      if (s.piece != none) {
        printw(" ");
        char unicode_piece[4] = "\xe2\x99\x93";
        unicode_piece[2] += s.piece + (s.color != sc) * 6;
        printw(unicode_piece);
        printw(" ");
      } else {
        printw("   ");
      }
    }
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(1));
    printw(" %d \n", y + 1);
  }
  printw("    a  b  c  d  e  f  g  h    \n");
  refresh();
}

void setup_mouse () {
  keypad(stdscr, TRUE);
  mousemask(BUTTON1_CLICKED, NULL);
  MEVENT event;
  while (1) {
    int ch = getch();
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
          addch('`' + event.x / 3);
          printw("%d\n", 9 - event.y);
        }
      }
    }
  }
}
