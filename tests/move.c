#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
enum piece { KING, ROOK, PAWN, BISHOP, ERR };

char **return_squares(enum piece p, const char *location, char *dest);

int main(void) {

  char *text = "a1";
  return_squares(BISHOP, "a4", "c2");

  return 0;
}

char **return_squares(enum piece p, const char *location, char *dest) {
  char MAX_ROW = '8', MAX_COLUMN = 'h';
  char template[3];
  if (p == ROOK) {
    if (*location == *dest) {
      char max = location[1] > dest[1] ? location[1] : dest[1];
      char min = location[1] > dest[1] ? dest[1] : location[1];
      // printf("%c%c\n", min,max);
      *template = *location;
      template[1] = min;
      template[2] = '\0';
      for (; template[1] < max; template[1] += 1) {
        printf("%s\n", template);
      }
    } else if (location[1] == dest[1]) {

      char max = *location > *dest ? *location : *dest;
      char min = *location > *dest ? *dest : *location;
      *template = min;
      template[1] = location[1];
      template[2] = '\0';
      for (; *template <max; *template += 1) {
        printf("%s\n", template);
      }
    }
  } else if (p == PAWN) {

    if (*location != *dest) {
      return NULL;
    }

    char max = location[1] > dest[1] ? location[1] : dest[1];
    char min = location[1] > dest[1] ? dest[1] : location[1];

    if (max - min == 2 &&
        1) { // here we will check if the pawn has already moved
    }
    *template = *location;
    template[1] = min;
    template[2] = '\0';
    for (; template[1] < max; template[1] += 1) {
      printf("%s\n", template);
    }

  } else if (p == BISHOP) {
    if(abs(*location - *dest) == (location[1] - dest[1])){
      strcpy(template, location);
      bool add_f = false,add_b = false;
      if(*template < *dest){
        add_f = true;
      }else ;
      if(template[1] < dest[1]) add_b = true;
      else ;

      for(; *template != *dest; add_f ? ++*template : --*template, add_b ? ++template[1] : --template[1]){
        printf("%s\n", template);
      }
    }else puts("WTF the BISHOP DOIN");
  } else if (location[1] != dest[1] && *location != *dest) {
    puts("CANNOT MOVE");
    return NULL;
  }

  return NULL;
}
