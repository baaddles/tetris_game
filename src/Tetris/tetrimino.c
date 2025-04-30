/**
 * @file tetrimino.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <ncurses.h>
#include <tetrimino.h>
#include <defines.h>

static const t_point TETRIMINO_SHAPES[TETRIS_TETRIMINO_NB][TETRIS_TETRIMINO_ORIENTATIONS][TETRIS_TETRIMINO_SIZE_YX] = {
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

void TetrisTetriminoDrawAll(WINDOW *win) {
    t_tetrimino tetrimino;
    for (int k = SHAPE_BEGIN; k < SHAPE_END; ++k) {     // FORME
        tetrimino.shape = k-1;
        wattron(win, A_REVERSE | COLOR_PAIR(k));

        for (int ori = 0; ori < TETRIS_TETRIMINO_ORIENTATIONS; ++ori) {         // ORIENTATION
            tetrimino.orientation = ori;
            TetriminoDraw(win, &tetrimino);
        }

    wattroff(win, A_REVERSE | COLOR_PAIR(k));
    }
}

void TetriminoDraw(WINDOW *win, t_tetrimino *tetrimino) {
    if (tetrimino->shape < SHAPE_I || tetrimino->shape > SHAPE_Z){
        return;
    }
    for (int co = 0; co < TETRIS_TETRIMINO_SIZE_YX; ++co) {
        wattron(win, A_REVERSE | COLOR_PAIR(tetrimino->shape));
        mvwprintw(
            win,
            tetrimino->location.y + TETRIMINO_SHAPES[tetrimino->shape - 1][tetrimino->orientation][co].y,
            tetrimino->location.x + TETRIMINO_SHAPES[tetrimino->shape - 1][tetrimino->orientation][co].x * TETRIS_TETRIMINO_SCALE_X,
            "%*c", TETRIS_TETRIMINO_SCALE_X, ' '
        );
        wattroff(win, A_REVERSE | COLOR_PAIR(tetrimino->shape));
    }
}

void TetriminoHide(WINDOW *win, t_tetrimino *tetrimino){
    if (tetrimino->shape < SHAPE_I || tetrimino->shape > SHAPE_Z){
        return;
    }
    for (int k = 0 ; k < TETRIS_TETRIMINO_SIZE_YX ; ++k){
        for (int m = 0 ; m < TETRIS_TETRIMINO_SIZE_YX ; ++m){
            mvwprintw(
            win,
            tetrimino->location.y + k,
            tetrimino->location.x + m * TETRIS_TETRIMINO_SCALE_X,
            "%*c", TETRIS_TETRIMINO_SCALE_X, ' ');
        }
    }
    wrefresh(win);
}

bool TetriminoCanFit(t_tetrimino *tetrimino, int yMax, int xMin, int xMax){
    if (tetrimino->location.x < xMax && tetrimino->location.x > xMin && tetrimino->location.y < yMax){
        return true;
    }
    else return false;
}

void TetriminoCenter(t_tetrimino *tetrimino, int width, int height){
    tetrimino->location.y = 1;
    tetrimino->location.x = (width / 2);
}

/*[] End of file */