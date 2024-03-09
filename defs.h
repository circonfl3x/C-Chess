#ifndef _DEFS_H
    #include <raylib.h>

    #define _DEFS_H 
    
    #define _CHESS_H 1
    #define WIDTH 1000
    #define HEIGHT 1000
    #define CELLWIDTH (WIDTH/8)
    #define CELLHEIGHT (HEIGHT/8)
    
    enum PIECE { KING = 1, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

    enum SIDE { CNONE = -1, CWHITE, CBLACK };
    typedef struct {
      enum PIECE piece;
      enum SIDE side;
      Vector2 coords;
      bool is_dead;
      bool has_moved;
      // int x;
      // int y;
      //char location[3];
    } piece;
    typedef struct
    {
        Color color;
        //bool is_occupied;
        enum SIDE side;
        int x;
        int y;
        // int relative_index;
        char location[3];
    } pos;

    typedef struct{
        bool is_locked;
        char location[3];
        Vector2 coords;
    }piece_lock;

    extern piece_lock lock;
    extern piece *active_piece;
#endif
