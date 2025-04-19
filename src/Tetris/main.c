#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "defines.h"

#define SEGMENT_WIDTH       10
#define SEGMENT_SPACING     2
#define HAUTEUR     10
#define LARGEUR     30

typedef enum e_shape {
    SHAPE_NONE = 0,
    SHAPE_BEGIN,
    SHAPE_I = SHAPE_BEGIN,
    SHAPE_J,
    SHAPE_L,
    SHAPE_O,
    SHAPE_S,
    SHAPE_T,
    SHAPE_Z,
    SHAPE_END
}t_shape;

typedef struct s_point{
    int y;
    int x;
}t_point;

const t_point TETRIMINO_SHAPES[TETRIS_TETRIMINO_NB][TETRIS_TETRIMINO_ORIENTATIONS][TETRIS_TETRIMINO_SIZE_YX] = {
    {   // I
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
    },
    {   // J
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
        {{0, 1}, {1, 1}, {2, 0}, {2, 1}},
    },
    {   // L
        {{0, 2}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    },
    {   // O
        {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
        {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
        {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
        {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
    },
    {   // S
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
        {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
        {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
    },
    {   // T
        {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
        {{0, 1}, {1, 0}, {1, 1}, {2, 1}},
    },
    {   // Z
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
        {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
        {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
        {{0, 1}, {1, 0}, {1, 1}, {2, 0}},
    }
};

int main(int argc, char**argv){
    printf("========== Enter Tetris Game ==========\n");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(0);

    box(stdscr, 0, 0);

    start_color();
    init_pair(SHAPE_I, COLOR_CYAN, COLOR_BLACK);
    init_pair(SHAPE_J, COLOR_BLUE, COLOR_BLACK);
    init_pair(SHAPE_L, COLOR_WHITE, COLOR_BLACK);
    init_pair(SHAPE_O, COLOR_YELLOW, COLOR_BLACK);
    init_pair(SHAPE_S, COLOR_GREEN, COLOR_BLACK);
    init_pair(SHAPE_T, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(SHAPE_Z, COLOR_RED, COLOR_BLACK);

    WINDOW *board = newwin(TETRIS_BOARD_HEIGHT, TETRIS_BOARD_WIDTH*2, TETRIS_BOARD_Y, TETRIS_BOARD_X*2);
    WINDOW *next = newwin(TETRIS_NEXT_HEIGHT, TETRIS_NEXT_WIDTH*2, TETRIS_NEXT_Y, TETRIS_NEXT_X*2);
    WINDOW *hold = newwin(TETRIS_HOLD_HEIGHT, TETRIS_HOLD_WIDTH*2, TETRIS_HOLD_Y, TETRIS_HOLD_X*2);
    WINDOW *display = newwin(TETRIS_DISPLAY_HEIGHT, TETRIS_DISPLAY_WIDTH*2, TETRIS_DISPLAY_Y, TETRIS_DISPLAY_X*2);

    // board
    box(board, 0, 0);
    mvwprintw(board, 1, 2, "BOARD");

    // next
    box(next, 0, 0);
    mvwprintw(next, 1, 2, "NEXT");

    // hold
    box(hold, 0, 0);
    mvwprintw(hold, 1, 2, "HOLD");

    // display
    mvwprintw(display, 1, 2, "DISPLAY");

    int ch;
    do{
        ch = getch();
        switch(ch){
            case 'q':
                break;
            default:
                break;
        }

        wrefresh(board);
        wrefresh(next);
        wrefresh(hold);
        wrefresh(display);

    }while(ch != 'q');

    wclear(stdscr);
    endwin();

    printf("========== Exit Tetris Game ==========\n");
    return EXIT_SUCCESS;
}