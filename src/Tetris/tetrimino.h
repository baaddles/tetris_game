#ifndef __TETRIMINO_H__
#define __TETRIMINO_H__

#include <stdbool.h>
#include <ncurses.h>

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

typedef struct s_tetrimino{
    t_shape shape;
    t_point location;
    int     orientation;
}t_tetrimino;

void TetrisTetriminoDrawAll(WINDOW*win);

void TetriminoDraw(WINDOW*win, t_tetrimino *tetrimino);
void TetriminoHide(WINDOW*win, t_tetrimino *tetrimino);
bool TetriminoCanFit(t_tetrimino *tetrimino, int yMax, int xMin, int xMax);
void TetriminoToTable(t_tetrimino *tetrimino, char *table, int nRow, int nCol);
void TetriminoCenter(t_tetrimino *tetrimino, int width, int height);

#endif