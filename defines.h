
/**
 * @file defines.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SPACEBAR        32
#define KEY_S           115

#define TETRIS_TETRIMINO_NB     7
#define TETRIS_TETRIMINO_ORIENTATIONS       4
#define TETRIS_TETRIMINO_SIZE_YX        4
#define TETRIS_TETRIMINO_SCALE_X        2

#define TETRIS_BOARD_Y      1
#define TETRIS_BOARD_X      1
#define TETRIS_BOARD_HEIGHT     22
#define TETRIS_BOARD_WIDTH      12

#define TETRIS_NEXT_Y       (TETRIS_BOARD_Y)
#define TETRIS_NEXT_X       (TETRIS_BOARD_X + TETRIS_BOARD_WIDTH + 1)
#define TETRIS_NEXT_HEIGHT      8
#define TETRIS_NEXT_WIDTH       8

#define TETRIS_HOLD_Y       (TETRIS_NEXT_Y + TETRIS_NEXT_HEIGHT + 1)
#define TETRIS_HOLD_X       (TETRIS_NEXT_X)
#define TETRIS_HOLD_HEIGHT      (TETRIS_NEXT_HEIGHT)
#define TETRIS_HOLD_WIDTH       (TETRIS_NEXT_WIDTH)

#define TETRIS_DISPLAY_Y        (TETRIS_HOLD_Y + TETRIS_HOLD_HEIGHT + 1)
#define TETRIS_DISPLAY_X        (TETRIS_NEXT_X)
#define TETRIS_DISPLAY_HEIGHT       8
#define TETRIS_DISPLAY_WIDTH        10

#endif
