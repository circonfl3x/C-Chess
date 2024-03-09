
#include "board.h"
#include "defs.h"
#include "extras.h"
#include <raylib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void init_board(pos **board)
{
  for(int rows = 0; rows < 8 ; ++rows){
    for(int columns = 0; columns < 8 ; ++columns){
      
      board[rows][columns].side = CNONE;
      if(rows % 2 == 0){      
        board[rows][columns].color = columns % 2 == 0? LIGHT : DARK;
      }else board[rows][columns].color = columns % 2 != 0 ? LIGHT:DARK;
      board[rows][columns].y = CELLWIDTH*columns;
      board[rows][columns].x = CELLHEIGHT*rows;
      // board[rows][columns].is_occupied = false;
      init_board_addrs(board, rows, columns);
      
    }
  }
}

// pos *board_location_by_char(pos **board, const char *location)
// {

//   // int *index = i_get_position(location);
//   // pos *ptr = &board[*index][index[1]];
//   // free(index);
//   // return ptr;
// }

pos *board_location_by_int(pos **board, int x, int y){
  Vector2 coords = coords_snap(x, y);
}

void print_board(pos **board)
{
  for(int rows = 0 ; rows  < 8 ; ++rows){
    for(int columns = 0 ; columns < 8; ++columns){
      
      //printf("OK %d %d\n", board[rows][columns].x, board[rows][columns].y);
      DrawRectangle(board[rows][columns].x,board[rows][columns].y ,CELLWIDTH ,CELLHEIGHT , board[rows][columns].color );
      
     }
  }
}
void print_text_overlay(pos **board){
  for(int rows = 0; rows < 8; ++rows){
    for(int columns = 0 ; columns < 8; ++columns){
      
      DrawText(board[rows][columns].location, board[rows][columns].x, board[rows][columns].y, 28, WHITE);
    }
  }
}
void free_board(pos **board){
  for(int rows = 0; rows < 8; ++rows) free(board[rows]);
  free(board);  
}

//Deprecated for now
// void boardWatch(pos **board, piece *p){
//   for(int rows = 0; rows < 8 ; ++rows){
//     for(int columns = 0; columns < 8; ++columns){
//       for(int i = 0 ; i < 32; ++i){
//         //TODO: Update for dead pieces, don't need to be decl
//         //TODO: Hash the locations for faster comparisons
//         //printf("%s\n", pieces[i].location);
//         if(strncmp(board[rows][columns].location,p[i].location,2 ) == 0){
//           // if(board[rows][columns].is_occupied == false)
//             // printf("%s\n", board[rows][columns].location);
//           //board[rows][columns].is_occupied = true;
//           board[rows][columns].side = p[i].side;
          
//         }else{
//           // board[rows][columns].is_occupied = false;
//           // board[rows][columns].side = CNONE;
//         }
//       }
//     }
//   }
// }
