#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(int argc, char**argv){
    printf("========== Start ==========\n");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(0);

    box(stdscr, 0, 0);

    mvwprintw(stdscr, 1, 1, "Appuyer sur q pour quitter le programme...");

    int ch;
    do{
        ch = getch();
        switch(ch){
            case 'q':
            break;
            default:
            break;
        }
    }while(ch != 'q');

    wclear(stdscr);
    endwin();

    printf("========== End ==========\n");
    return EXIT_SUCCESS;
}
