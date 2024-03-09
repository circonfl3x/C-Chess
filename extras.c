#include "extras.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <raylib.h>
// //Deprecated
// int *location_to_addr(const char *location)
// {
//   if(strlen(location) != 2){
//     printf("Wrong location: %s\n (Memory is leaked in this routine. Will be fixed)", location);
//     exit(1);
//   }

//   int rows = ((int)(*location))-97; //convert char 'char' to int
//   int columns = (int)location[1]-48; //convert char 'int' to int
//   int *ret = malloc(sizeof(int) * 2);
//   ret[0] = rows;
//   ret[1] = columns;
//   return ret;
// }

int ascii_to_int(char a){
  return a-48;
}

char int_to_ascii(int a){
  return a+48;
}

char increment_ascii(char a){
  return int_to_ascii(ascii_to_int(a)+1);
}
char permute_ascii(char a, int b){
  return int_to_ascii(ascii_to_int(a) + b);
}
void init_board_addrs(pos **b, int rows, int columns){
  if(rows > 7 || columns > 7 || rows < 0 || columns < 0) {
    puts("wrong address given");
    exit(1);
  }
  char first = (char)(rows+97);
  char last = (char)(8-columns)+48;
  
  char location[3];
  *location = first;
  location[1] = last;
  location[2] = '\0';
  strcpy(b[rows][columns].location, location);
}

Vector2 location_to_coords(const char *addr){
  if(strlen(addr) != 2){
    puts("Wrong address given");
    exit(1);
  }
  // int *m = malloc(2);
  // *m = ((int)*(addr-97)) * CELLWIDTH;
  // m[1] = (int)*((8+addr)-48) * CELLHEIGHT;

  Vector2 ret;
  ret.x = (float) ((*addr-97)) * CELLWIDTH;  
  //printf("%d\n", addr[1]-48);
  ret.y = (float) (HEIGHT - (addr[1]-48) * CELLHEIGHT);
  return ret;
}


//Deprecated
// int *i_get_position(const char *addr){ 
//   if(strlen(addr) != 2){
    
//     puts("Wrong address given");
//     exit(1);
//   }
//   // int *m = malloc(2);
//   // *m = ((int)*(addr-97)) * CELLWIDTH;
//   // m[1] = (int)*((8+addr)-48) * CELLHEIGHT;

//   int *ret = malloc(sizeof(int) * 2);
//   ret[0] = (float) ((*addr-97)) * CELLWIDTH;  
//   ret[1] = (float) ((addr[1]-48) * (HEIGHT-CELLHEIGHT*(addr[1]-48)));
//   return ret;
// }
//CAUTION: returns memory on the heap will have to be sorted with

char *coords_to_location(int x, int y){
  int xPos = WIDTH,yPos=HEIGHT;
  int current = INT_MAX;
  for(int est = 0; est <= WIDTH; est+=CELLWIDTH){
    // printf("%d\n", abs(est-x));
    if(abs(est - x) < current){
      if(est > x) continue;
      xPos = est;
      current = abs(est-x);
    }
  }

  current = INT_MAX;
  for(int est = 0; est <= HEIGHT; est+=CELLHEIGHT){
    if(abs(est - y) < current){
      if(est > y) continue;
      yPos = est;
      current = abs(est-y);
    }
  }
  char *ret = malloc(3);
  // printf("%d %d\n", xPos, yPos);
  snprintf(ret,3, "%c%c",xPos/CELLWIDTH+97,8-(yPos/CELLHEIGHT)+48);
  
  return ret;
}

Vector2 coords_snap(int x, int y){
    
int xPos = WIDTH,yPos=HEIGHT;
  int current = INT_MAX;
  for(int est = 0; est <= WIDTH; est+=CELLWIDTH){
    // printf("%d\n", abs(est-x));
    if(abs(est - x) < current){
      if(est > x) continue;
      xPos = est;
      current = abs(est-x);
    }
  }

  current = INT_MAX;
  for(int est = 0; est <= HEIGHT; est+=CELLHEIGHT){
    if(abs(est - y) < current){
      if(est > y) continue;
      yPos = est;
      current = abs(est-y);
    }
  }

  Vector2 ret;
  ret.x = xPos;
  ret.y = yPos;

  return ret;
}

bool vec_cmp(Vector2 vec1, Vector2 vec2){
  if(vec1.x == vec2.x && vec1.y == vec2.y){
    return true;
  }  

  return false;
}
