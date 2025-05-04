#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <defines.h>
#include <tetris.h>
#include <tetrimino.h>

int main(int argc, char**argv){
    printf("========== Enter Tetris Game ==========\n");

    TetrisInit();
    box(stdscr, 0, 0);
   // TetrisTetriminoDrawAll(stdscr);

    int ch;
    do{
        ch = getch();

        switch (ch){
        case 'q':
            break;
        default:
            TetrisOnKey(ch);
            break;
        }
        
        TetrisDraw();

    }while(ch != 'q');

    TetrisClose();

    printf("========== Exit Tetris Game ==========\n");
    return EXIT_SUCCESS;
}
