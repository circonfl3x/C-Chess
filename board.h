#include <raylib.h>
#ifndef _BOARD_H
    #define _BOARD_H 1
    #include <stdbool.h>
    #include <raylib.h>
    #include "defs.h"
    #define DARK DARKBROWN
    #define LIGHT BROWN
    typedef struct{
        int rows;
        int columns;
    } BoardIndex2;

    extern pos **board;
    extern void init_board(pos **board);
    extern void print_board(pos **board);
    extern void free_board(pos **board);
    extern void print_text_overlay(pos **board);
    // extern pos *board_location_by_char(pos **board, const char *location);
    // extern void boardWatch(pos **board, piece *p); //updates piece info
#endif
