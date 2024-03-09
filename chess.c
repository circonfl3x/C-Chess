#include "chess.h"
#include "board.h"
#include "pieces.h"
#include "extras.h"
#include "mouse.h"
#include <raylib.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
int main(void) {
  InitWindow(WIDTH, HEIGHT, "Chess");
  SetTargetFPS(30);
  board = NULL;

  board = malloc(sizeof(pos*)*8);
  for(int i = 0 ; i < 8; ++i){
    *(board+i) = malloc(sizeof(pos) * 8);
  }
  // char buff[256];

  //Init pieces and board
  init_references();
  loadPieces();
  pieces = malloc(sizeof(piece)*32);
  
  init_board(board);
  initPieces(pieces);

  //misc
  lock.is_locked = false;
  lock.coords.x = INT_MAX;
  lock.coords.y = INT_MAX;
  
  //memcpy(board, NULL, sizeof(pos)*64);
  while (!WindowShouldClose()) {
    // boardWatch(board, pieces);
    BeginDrawing();
    ClearBackground(WHITE);
    // DrawRectangle(250, 250, 50, 50, BLACK);
    // sprintf(buff,"%2.f, %2.f",get_position("b1").x,get_position("b1").y);
  
    print_board(board);
    
    //WARNING: Every draw call should be done after printing the board
    drawOnSelected();
    print_text_overlay(board);
    drawPieces(pieces);
    EndDrawing();
  }
  
  unloadPieces();
  free(pieces);
  free_board(board);
  CloseWindow();
  
  return 0;
}
