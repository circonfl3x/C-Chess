#ifndef _MOUSE_H
  #define _MOUSE_H 1
  #include "defs.h"
  enum move_state{
  ERROR=-1,SUCCESS,IS_TREASON,IS_EAT,IS_BLOCKED
  };
  char *approximate_mouse_location();
  void drawOnSelected();
  void drawPossible(piece *p);
#endif
