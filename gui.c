#include "gui.h"

int mouse_x_prev = -1;
int mouse_y_prev = -1;

void setup_window () {
  initscr();
  clear();
  noecho();
  curs_set(0);
  cbreak();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);
}

void draw_board_with_highlight (arrayboard *a, int x_highlight, int y_highlight) {
  clear();
  printw("    a  b  c  d  e  f  g  h    \n");
  for (int y = 7; y >= 0; y--) {
    printw(" %d ", y + 1);
    for (int x = 0; x < 8; x++) {
      square s = (*a)[y][x];
      int unicode_offset;
      if (x != x_highlight || y != y_highlight) {
        color sc = y % 2 == x % 2;
        if (sc) {
          attron(COLOR_PAIR(2));
        } else {
          attron(COLOR_PAIR(1));
        }
        unicode_offset = s.piece + (s.color != sc) * 6;
      } else {
        if (s.color == black) {
          attron(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(4));
        }
        unicode_offset = s.piece + (s.color == white) * 6;
      }
      if (s.piece != none) {
        printw(" ");
        char unicode_piece[4] = "\xe2\x99\x93";
        unicode_piece[2] += unicode_offset;
        printw(unicode_piece);
        printw(" ");
      } else {
        printw("   ");
      }
    }
    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(1));
    printw(" %d \n", y + 1);
  }
  printw("    a  b  c  d  e  f  g  h    \n");
  refresh();
}

void draw_arrayboard (arrayboard *a) {
  draw_board_with_highlight(a, -1, -1);
}

void highlight_board (arrayboard *a, int x, int y) {
  draw_board_with_highlight(a, x, y);
}

void setup_mouse (arrayboard *a) {
  keypad(stdscr, TRUE);
  mousemask(BUTTON1_CLICKED, NULL);
  MEVENT event;
  while (1) {
    int ch = getch();
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
          mouse_clicked(a, &event);
        }
      }
    }
  }
}

void mouse_clicked (arrayboard *a, MEVENT *e) {
  int x = e->x / 3 - 1;
  int y = 8 - e->y;
  // addch('a' + x);
  // printw("%d\n", y + 1);
  if (0 <= x && x < 8 && 0 <= y && y < 8) {
    if (mouse_x_prev == -1) {
      if (clickable(a, x, y)) {
        mouse_x_prev = x;
        mouse_y_prev = y;
        highlight_board(a, x, y);
      }
    } else {
      int status = update_boards(a, mouse_x_prev, mouse_y_prev, x, y);
      if (status) {
        draw_arrayboard(a);
        mouse_x_prev = -1;
      } else {
        printw("invalid move\n");
      }
    }
  } else {
    mouse_x_prev = -1;
    draw_arrayboard(a);
  }
}
