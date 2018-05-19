#include "gui.h"

guiboard_t guiboard = {};

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

void setup_board () {
  for (int y = 7; y >= 0; y--) {
    for (int x = 0; x < 8; x++) {
      guisquare_t *s = &guiboard[y][x];
      s->square_color = y % 2 == x % 2;
    }
  }
}

void arrayboard_to_guiboard () {
  for (int y = 7; y >= 0; y--) {
    for (int x = 0; x < 8; x++) {
      square as = arrayboard[y][x];
      guisquare_t *gs = &guiboard[y][x];
      gs->piece = as.piece;
      gs->piece_color = as.color;
    }
  }
}

void draw_board () {
  arrayboard_to_guiboard();
  clear();
  printw("    a  b  c  d  e  f  g  h    \n");
  for (int y = 7; y >= 0; y--) {
    printw(" %d ", y + 1);
    for (int x = 0; x < 8; x++) {
      guisquare_t s = guiboard[y][x];
      int unicode_offset;
      if (s.highlight) {
        if (s.piece_color == black) {
          attron(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(4));
        }
        unicode_offset = s.piece + !s.piece_color * 6;
      } else {
        if (s.square_color == white) {
          attron(COLOR_PAIR(1));
        } else {
          attron(COLOR_PAIR(2));
        }
        unicode_offset = s.piece + (s.piece_color != s.square_color) * 6;
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

void setup_mouse () {
  keypad(stdscr, TRUE);
  mousemask(BUTTON1_CLICKED, NULL);
  MEVENT event;
  while (1) {
    int ch = getch();
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
          mouse_clicked(&event);
        }
      }
    }
  }
}

void mouse_clicked (MEVENT *e) {
  int x = e->x / 3 - 1;
  int y = 8 - e->y;
  // addch('a' + x);
  // printw("%d\n", y + 1);
  if (0 <= x && x < 8 && 0 <= y && y < 8) {
    if (mouse_x_prev == -1) {
      if (clickable(x, y)) {
        mouse_x_prev = x;
        mouse_y_prev = y;
        guiboard[y][x].highlight = 1;
        draw_board();
      }
    } else {
      int status = update_boards(mouse_x_prev, mouse_y_prev, x, y);
      if (status) {
        guiboard[mouse_y_prev][mouse_x_prev].highlight = 0;
        draw_board();
        mouse_x_prev = -1;
      } else {
        printw("invalid move\n");
      }
    }
  } else {
    mouse_x_prev = -1;
    draw_board();
  }
}
