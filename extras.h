
#ifndef _EXTRAS_H
  #define _EXTRAS_H 1
  #include "board.h"
  extern void init_board_addrs(pos **b, int rows, int columns);

  #define estimate(x) _Generic((x), int:estimate_int,Vector2: estimate_vec,other:err)(x);
  extern char *coords_to_location(int x, int y);
  extern Vector2 coords_snap(int x, int y);
  extern Vector2 location_to_coords(const char *addr);
  // int *i_get_position(const char *addr);
  extern char *estimate_vec(int x, int y);
  extern int ascii_to_int(char a);
  extern char int_to_ascii(int a);
  extern char increment_ascii_int(char a);
  extern char permute_ascii_int(char a, int b);
  extern char increment_ascii(char a);
  extern bool vec_cmp(Vector2 vec1, Vector2 vec2);
  extern void err(void *x);
#endif
