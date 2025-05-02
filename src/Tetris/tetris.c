/**
 * @file tetris.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <ncurses.h>
#include <stdlib.h>

#include <tetris.h>
#include <defines.h>
#include <tetrimino.h>

static WINDOW *wBoard = NULL;
static WINDOW *wNext = NULL;
static WINDOW *wHold = NULL;
static WINDOW *wDisplay = NULL;

static t_tetrimino tetrimino = {0};
static t_tetrimino tetriNext = {0};
static t_tetrimino tetriHold = {0};

static int dBoard = 0;

void TetrisInit(void){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(0);

    tetrimino.shape = SHAPE_NONE;
    tetriNext.shape = SHAPE_NONE;
    tetriHold.shape = SHAPE_NONE;
    dBoard = 0;

    start_color();
    init_pair(SHAPE_I, COLOR_CYAN, COLOR_BLACK);
    init_pair(SHAPE_J, COLOR_BLUE, COLOR_BLACK);
    init_pair(SHAPE_L, COLOR_WHITE, COLOR_BLACK);
    init_pair(SHAPE_O, COLOR_YELLOW, COLOR_BLACK);
    init_pair(SHAPE_S, COLOR_GREEN, COLOR_BLACK);
    init_pair(SHAPE_T, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(SHAPE_Z, COLOR_RED, COLOR_BLACK);
    init_pair(SHAPE_NONE, COLOR_BLACK, COLOR_BLACK);

    wBoard = newwin(TETRIS_BOARD_HEIGHT, TETRIS_BOARD_WIDTH*TETRIS_TETRIMINO_SCALE_X, TETRIS_BOARD_Y, TETRIS_BOARD_X*TETRIS_TETRIMINO_SCALE_X);
    box(wBoard, 0, 0);

    wNext = newwin(TETRIS_NEXT_HEIGHT, TETRIS_NEXT_WIDTH*TETRIS_TETRIMINO_SCALE_X, TETRIS_NEXT_Y, TETRIS_NEXT_X*TETRIS_TETRIMINO_SCALE_X);
    box(wNext, 0, 0);

    wHold = newwin(TETRIS_HOLD_HEIGHT, TETRIS_HOLD_WIDTH*TETRIS_TETRIMINO_SCALE_X, TETRIS_HOLD_Y, TETRIS_HOLD_X*TETRIS_TETRIMINO_SCALE_X);
    box(wHold, 0, 0);

    wDisplay = newwin(TETRIS_DISPLAY_HEIGHT, TETRIS_DISPLAY_WIDTH*TETRIS_TETRIMINO_SCALE_X, TETRIS_DISPLAY_Y, TETRIS_DISPLAY_X*TETRIS_TETRIMINO_SCALE_X);
    box(wDisplay, 0, 0);
}

void TetrisClose(void){
    wclear(stdscr);
    endwin();
}

void TetrisTetriminoRand(t_tetrimino *tetrimino){
    int idx = rand() % TETRIS_TETRIMINO_NB; // 0..6
    tetrimino->shape = SHAPE_I + idx;       // 1..7
    tetrimino->orientation = 0;
    tetrimino->location.y = TETRIS_BOARD_Y;
    tetrimino->location.x = TETRIS_BOARD_WIDTH / 2 + 2;
}

void TetrisHold(void){
    if (tetriHold.shape  == SHAPE_NONE && tetrimino.shape != SHAPE_NONE){
        TetriminoHide(wHold, &tetriHold);
        TetriminoHide(wBoard, &tetrimino);
        TetriminoSwitch(&tetrimino, &tetriHold);
        TetriminoCenter(&tetriHold, TETRIS_HOLD_WIDTH, TETRIS_HOLD_HEIGHT);
        TetriminoDraw(wHold, &tetriHold);
        dBoard = 0;
    }

    if (tetriHold.shape != SHAPE_NONE && tetrimino.shape != SHAPE_NONE){
        TetriminoHide(wBoard, &tetrimino);
        TetriminoHide(wHold, &tetriHold);
        TetriminoSwitch(&tetrimino, &tetriHold);
        TetriminoCenter(&tetrimino, TETRIS_BOARD_WIDTH, TETRIS_BOARD_HEIGHT);
        TetriminoDraw(wBoard, &tetrimino);
        TetriminoCenter(&tetriHold, TETRIS_HOLD_WIDTH, TETRIS_HOLD_HEIGHT);
        TetriminoDraw(wHold, &tetriHold);
    }
}

void TetrisDraw(void){
    if (tetriNext.shape == SHAPE_NONE){
        TetrisTetriminoRand(&tetriNext);
        TetriminoCenter(&tetriNext, TETRIS_NEXT_WIDTH, TETRIS_NEXT_HEIGHT);
        TetriminoDraw(wNext, &tetriNext);
    }

    if (!dBoard && tetriNext.shape != SHAPE_NONE){
        TetriminoHide(wBoard, &tetrimino);

        tetrimino = tetriNext;
        TetriminoCenter(&tetrimino, TETRIS_BOARD_WIDTH, TETRIS_BOARD_HEIGHT);
        TetriminoDraw(wBoard, &tetrimino);

        TetriminoHide(wNext, &tetriNext);
        tetriNext.shape = SHAPE_NONE;

        dBoard = 1;
    }

    wrefresh(wBoard);
    wrefresh(wNext);
    wrefresh(wHold);
    wrefresh(wDisplay);
}

void TetrisOnKey(int key){
    switch (key){
    case KEY_DOWN:
        TetriminoHide(wBoard, &tetrimino);
        tetrimino.location.y += 1;
        if (!TetriminoCanFit(&tetrimino, TETRIS_BOARD_HEIGHT, 0, TETRIS_BOARD_WIDTH)){
            tetrimino.location.y -= 1;
        }
        TetriminoDraw(wBoard, &tetrimino);
        break;
    case KEY_UP:
        TetriminoHide(wBoard, &tetrimino);
        int rotaTemp = tetrimino.orientation;
        TetriminoRota(&tetrimino);
        if (!TetriminoCanFit(&tetrimino, TETRIS_BOARD_HEIGHT, 0, TETRIS_BOARD_WIDTH)){
            tetrimino.orientation = rotaTemp;
        }
        TetriminoDraw(wBoard, &tetrimino);
        break;
    case KEY_LEFT:
        TetriminoHide(wBoard, &tetrimino);
        tetrimino.location.x -= 2;
        if (!TetriminoCanFit(&tetrimino, TETRIS_BOARD_HEIGHT, 0, TETRIS_BOARD_WIDTH)){
            tetrimino.location.x += 2;
        }
        TetriminoDraw(wBoard, &tetrimino);
        break;
    case KEY_RIGHT:
    TetriminoHide(wBoard, &tetrimino);
    tetrimino.location.x += 2;
        if (!TetriminoCanFit(&tetrimino, TETRIS_BOARD_HEIGHT, 0, TETRIS_BOARD_WIDTH)){
            tetrimino.location.x -= 2;
        }
        TetriminoDraw(wBoard, &tetrimino);
        break;
    case KEY_S:
        if (dBoard){
            TetriminoHide(wBoard, &tetrimino);
            dBoard = 0;
        }
        break;
    case SPACEBAR:
        TetrisHold();
        break;
    default:
        break;
    }
}



/*[] End of file*/
