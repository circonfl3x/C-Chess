#include "mouse.h"
#include "board.h"
#include "defs.h"
#include "extras.h"
#include "pieces.h"
#include <limits.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum move_state move(piece *p, Vector2 coords);

void drawOnSelected() {

  if (lock.is_locked) {

    // printf("%s\n", lock.location);
    // TODO: Draw Possible combinations deprecated for now coz too much work
    // if(active_piece != NULL) drawPossible(active_piece);
    DrawRectangle(lock.coords.x, lock.coords.y, CELLWIDTH, CELLHEIGHT,
                  is_occupied(pieces, lock.location) ? RED : BLUE);

  } else
    ;

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // left click

    int MouseX = GetMouseX(), MouseY = GetMouseY();

    Vector2 location = coords_snap(MouseX, MouseY);

    if (vec_cmp(lock.coords, location)) {
      // toggle if same location

      lock.is_locked = lock.is_locked ? false : true;

    } else {

      char *loc = coords_to_location(MouseX, MouseY);

      if (lock.is_locked && active_piece != NULL) {
        enum move_state m = move(active_piece, location);
        if (m == IS_TREASON) {
          lock.coords.x = active_piece->coords.x;
          lock.coords.y = active_piece->coords.y;
        } else {
          lock.is_locked = false;
          lock.coords.x = INT_MAX;
          lock.coords.y = INT_MAX;
        }
        // active_piece = NULL;
      } else {

        // printf("%s\n", piece_occupying(pieces, loc));
        // DrawRectangle(location.x,location.y,CELLWIDTH
        // ,CELLHEIGHT,is_occupied(pieces, loc) ? RED : BLUE );
        strcpy(lock.location, loc);

        active_piece = piece_occupying(pieces, loc);
        lock.coords = location;
        lock.is_locked = true;
      }
      free(loc);
    }
  } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    lock.is_locked = false;
  }
}

enum move_state move(piece *p, Vector2 coords) {
  char *location_to_move = coords_to_location(coords.x, coords.y);
  char *current_location = coords_to_location(p->coords.x, p->coords.y);

  piece *ptr = v_piece_occupying(pieces, coords);
  bool is_valid_move = true, is_treason = false, is_eaten = false;
  
  bool queen_has_moved = false;
  switch (p->piece) {
  case PAWN:
    // printf("%c%d\n\n", *current_location, current_location[1]-48);
    //  printf("%d\n\n", (location_to_move[1]-48) - (current_location[1]-48));
    if (abs(*location_to_move - *current_location) == 1 &&
                location_to_move[1] - current_location[1] == p->side == CWHITE
            ? 1
            : 0) { // pawn eating logic

      piece *tmp;
      if ((tmp = piece_occupying(pieces, location_to_move)) != NULL) {
        // if (tmp->side == p->side) {
        //   puts("Pawn cannot eat one of own");
        //   is_valid_move = false;
        //   is_treason = true;
        // }
      } else
        is_valid_move = false;
    } else if (*location_to_move != *current_location)
      is_valid_move = false;
    else if (ascii_to_int(location_to_move[1]) -
                 ascii_to_int(current_location[1]) ==
             (p->side == CWHITE ? 1 : -1)) { // pawn single move forward
      // if(is_blocked(pieces, current_location ,location_to_move)){
      //   puts("BLOCKED!");
      //   is_valid_move = false;
      // }
      if (is_blocked(pieces, current_location, location_to_move)) {
        is_valid_move = false;
      }
    } else if (ascii_to_int(location_to_move[1]) -
                       ascii_to_int(current_location[1]) ==
                   (p->side == CWHITE ? 2 : -2) &&
               !p->has_moved) { // first double move for pawn
      if (is_blocked(pieces, current_location, location_to_move)) {
        is_valid_move = false;
      }
      // if(is_blocked(pieces, current_location ,location_to_move)){
      //    puts("BLOCKED DOUBLE MOVE!");
      //    is_valid_move = false;
      //  }
    } else {
      is_valid_move = false;
    }

    if (is_valid_move) { // checking for promotion //TODO: Different pieces?

      if (p->side == CWHITE ? location_to_move[1] == '8'
                            : location_to_move[1] == '1') {
        p->piece = QUEEN; // promotion?
      }
    }

    // if (is_valid_move &&
    //     is_blocked(pieces, current_location, location_to_move) &&
    //     p->piece != PAWN) {
    //   puts("PAWN blocked");
    //   is_valid_move = false;
    // }

    break;

  case KING: // we don't check whether the king is blocked but it somehow
             // working
    // TODO: Add castling and check mechanics?
    if (abs(*location_to_move - *current_location) > 1) {
      is_valid_move = false;
    }

    if (abs(ascii_to_int(location_to_move[1]) -
            ascii_to_int(current_location[1])) < 2)
      ;
    else {
      is_valid_move = false;
    }
    break;

  case ROOK:
    if (*location_to_move != *current_location) {
      if (location_to_move[1] !=
          current_location[1]) { // make sure the rook cannot move diagonally
        is_valid_move = false;
      }
      // check if piece is blocked
    }

    if (is_valid_move && is_blocked(p, location_to_move, current_location)) {
      puts("ROOK is blocked");
      is_valid_move = false;
    }
    break;

  case BISHOP:
    if (abs(*location_to_move - *current_location) ==
        (location_to_move[1] - current_location[1])) { // same diagonal
      piece *tmp;
      if (is_blocked(p, current_location, location_to_move)) {
        puts("BISHOP is blocked");
        is_valid_move = false;
      }
    }
    break;

  case KNIGHT:
    // knight needs nothing
    if (abs(*location_to_move - *current_location) == 2 &&
        abs(location_to_move[1] - current_location[1]) == 1) { // knight L 1
    } else if (abs(*location_to_move - *current_location) == 1 &&
               abs(location_to_move[1] - current_location[1]) == 2) {
    } else {
      puts("KNIGHT?");
      is_valid_move = false;
    }
    break;

  case QUEEN:
    //BISHOP MOVEMENT FOR QUEEN
    if (abs(*location_to_move - *current_location) ==
        abs(location_to_move[1] - current_location[1])) { // same diagonal
      piece *tmp;
      if (is_blocked(p, current_location, location_to_move)) {
        puts("QUEEN is blocked");
        is_valid_move = false;
      }else queen_has_moved = true;
    }
    //ROOK MOVEMENT FOR QUEEN
    else if (*location_to_move != *current_location) {
      if (location_to_move[1] !=
          current_location[1]) { // make sure the rook cannot move diagonally
        is_valid_move = false;
      }
      // check if piece is blocked
    }
    if (!queen_has_moved && is_valid_move && is_blocked(p, location_to_move, current_location)) {
      puts("QUEEN is blocked");
      is_valid_move = false;
    }
  break;
  }

  // end case

  if (ptr != NULL && is_valid_move) {
    if (ptr->side == p->side) { // check for treason
      puts("TREASON!");
      is_valid_move = false;
      active_piece = ptr;
      is_treason = true;
    } else {
      ptr->is_dead = true;
      // strcpy(ptr->location, "z0");
      ptr->coords.x = INT_MAX;
      ptr->coords.y = INT_MAX;
      is_eaten = true;
    }
  } else {

    piece *ptr;
    if ((ptr = v_piece_occupying(pieces, coords)) != NULL) {
      is_treason = true;
      active_piece = ptr;
    }
  }

  // strcpy(p->location, location);
  if (is_valid_move) {

    // printf("%s->%s\n", current_location, location_to_move);
    p->coords.x = coords.x;
    p->coords.y = coords.y;
    if (!p->has_moved)
      p->has_moved = true;
  } else
    printf("Cannot move to %s\n", location_to_move);
  free(location_to_move);
  free(current_location);
  if (is_treason)
    return IS_TREASON;
  else if (is_valid_move)
    return SUCCESS;
  else if (is_eaten)
    return IS_EAT;
  else
    return ERROR;
}
void drawPossible(piece *p) {
  char *location = coords_to_location(p->coords.x, p->coords.y);
  if (p->piece == PAWN) {
    location[1] = increment_ascii(location[1]);
    Vector2 coords = location_to_coords(location);
    DrawRectangle(coords.x, coords.y, CELLWIDTH, CELLHEIGHT, PINK);
    if (!p->has_moved) {
      location[1] = increment_ascii(location[1]);
      coords = location_to_coords(location);
      DrawRectangle(coords.x, coords.y, CELLWIDTH, CELLHEIGHT, PINK);
    }
  } else if (p->piece == ROOK) {
  }
  free(location);
}
