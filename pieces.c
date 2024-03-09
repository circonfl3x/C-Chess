
#include "pieces.h"
#include "defs.h"
#include "extras.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p_inherit_pos(piece *p, pos *b) {
  // strncpy(p->location, b->location, 3);
  p->coords.x = b->x;
  p->coords.y = b->y;
}

void init_references() {
  i_pieces = malloc(sizeof(Image *) * 13);
  i_pieces[0] = &i_wpawn;
  i_pieces[1] = &i_wknight;
  i_pieces[2] = &i_wbishop;
  i_pieces[3] = &i_wrook;
  i_pieces[4] = &i_wqueen;
  i_pieces[5] = &i_wking;

  i_pieces[6] = &i_bpawn;
  i_pieces[7] = &i_bknight;
  i_pieces[8] = &i_bbishop;
  i_pieces[9] = &i_brook;
  i_pieces[10] = &i_bqueen;
  i_pieces[11] = &i_bking;
  i_pieces[12] = NULL;

  textures = malloc(sizeof(Texture2D *) * 13);
  textures[0] = &wpawn;
  textures[1] = &wknight;
  textures[2] = &wbishop;
  textures[3] = &wrook;
  textures[4] = &wqueen;
  textures[5] = &wking;

  textures[6] = &bpawn;
  textures[7] = &bknight;
  textures[8] = &bbishop;
  textures[9] = &brook;
  textures[10] = &bqueen;
  textures[11] = &bking;
  textures[12] = NULL;
}

void initPieces(piece *p) { // DEFAULT BOARD SETUP
  for (int i = 0; i < 32; ++i) {
    p[i].is_dead = false;
    p[i].has_moved = false;
  }
  // WHITE DEFS ALWAYS BEFORE BLACK IN EACH SECTION
  // first 16 locations is pawns
  for (int i = 0; i < 8; ++i) {
    p[i].piece = PAWN;
    p[i].side = CWHITE;
    // printf("%d %d\n", board[1][i].x, board[1][i].y);
    p_inherit_pos(&p[i], &board[i][6]);

    p[i + 8].piece = PAWN;
    p[i + 8].side = CBLACK;
    p_inherit_pos(&p[i + 8], &board[i][1]);
  }
  // next 4 locations is KNIGHTS

  for (int i = 16; i < 20; ++i) {
    p[i].piece = KNIGHT;
    p[i].side = i > 17 ? CBLACK : CWHITE;
  }

  p_inherit_pos(&p[16], &board[1][7]); // Nb1
  p_inherit_pos(&p[17], &board[6][7]); // Ne1
  p_inherit_pos(&p[18], &board[1][0]); // Nb8
  p_inherit_pos(&p[19], &board[6][0]); // Ng8
  // next 2 locations is LIGHT BISHOP

  p[20].piece = BISHOP;
  p[20].side = CWHITE;
  p_inherit_pos(&p[20], &board[2][7]); // Bc1

  p[21].piece = BISHOP;
  p[21].side = CWHITE;
  p_inherit_pos(&p[21], &board[5][7]); // Bf1

  // next 2 locations is DARK BISHOP

  p[22].piece = BISHOP;
  p[22].side = CBLACK;
  p_inherit_pos(&p[22], &board[2][0]); // Bc8

  p[23].piece = BISHOP;
  p[23].side = CBLACK;
  p_inherit_pos(&p[23], &board[5][0]); // Bf8

  // next 4 locations is the rooks
  for (int i = 24; i < 28; ++i) {
    p[i].piece = ROOK;
    p[i].side = i > 25 ? CBLACK : CWHITE;
  }
  p_inherit_pos(&p[24], &board[0][7]); // Ra8
  p_inherit_pos(&p[25], &board[7][7]); // Re8

  p_inherit_pos(&p[26], &board[7][0]); // Ra1
  p_inherit_pos(&p[27], &board[0][0]); // Re1

  // next 2 is the queen
  p[28].piece = QUEEN;
  p[29].piece = QUEEN;
  p[28].side = CWHITE;
  p[29].side = CBLACK;
  p_inherit_pos(&p[28], &board[3][7]); // Qd3
  p_inherit_pos(&p[29], &board[3][0]); // Qd8
  // last 2 locations is the kings

  p[30].piece = KING;
  p[31].piece = KING;
  p[30].side = CWHITE;
  p[31].side = CBLACK;
  p_inherit_pos(&p[30], &board[4][7]); // Ke3

  p_inherit_pos(&p[31], &board[4][0]); // Ke8
}

Texture2D *piece_to_texture(enum PIECE p, enum SIDE s) {
  if (s == CWHITE) {
    switch (p) {
    case PAWN:
      return &wpawn;
      break;

    case KNIGHT:
      return &wknight;
      break;

    case BISHOP:
      return &wbishop;
      break;

    case ROOK:
      return &wrook;
      break;

    case QUEEN:
      return &wqueen;
      break;

    case KING:
      return &wking;
      break;

    default:
      puts("Cannot find texture!");
      exit(1);
      break;
    }
  } else if (s == CBLACK) {
    switch (p) {
    case PAWN:
      return &bpawn;
      break;

    case KNIGHT:
      return &bknight;
      break;

    case BISHOP:
      return &bbishop;
      break;

    case ROOK:
      return &brook;
      break;

    case QUEEN:
      return &bqueen;
      break;

    case KING:
      return &bking;
      break;

    default:
      puts("Cannot find texture!");
      exit(1);
      break;
    }
  }
  puts("Cannot find texture (How did we get here?)");
  exit(1);
  return NULL; // control will never reach here just to suppress warnings
}

bool is_occupied(piece *p, char *location) {
  if (strlen(location) != 2) {
    printf("Wrong location '%s'\n", location);
    exit(1);
  }
  Vector2 coords = location_to_coords(location);
  for (int i = 0; i < 32; ++i) {
    if (vec_cmp(coords, p[i].coords)) {
      return true;
    }
  }
  return false;
}

char *name_occupying(piece *p, char *location) {
  Vector2 coords = location_to_coords(location);
  for (int i = 0; i < 32; ++i) {
    if (vec_cmp(coords, p->coords)) {
      switch (p[i].piece) {
      case KING:
        return "King";
        break;

      case QUEEN:
        return "Queen";
        break;

      case ROOK:
        return "Rook";
        break;

      case BISHOP:
        return "Bishop";
        break;

      case KNIGHT:
        return "Knight";
        break;

      case PAWN:
        return "Pawn";
        break;
      }
    }
  }
  return "None";
}

piece *piece_occupying(piece *p, char *location) {
  Vector2 coords = location_to_coords(location);
  for (int i = 0; i < 32; ++i) {
    if (vec_cmp(coords, p[i].coords)) {
      return &p[i];
    }
  }
  return NULL; // deal with this well
}
// piece *i_piece_occupying(piece *p, int x, int y){}

piece *i_piece_occupying(piece *p, int x, int y) {
  Vector2 coords;
  coords.x = x;
  coords.y = y;

  for (int i = 0; i < 32; ++i) {
    if (vec_cmp(coords, p[i].coords)) {
      return &p[i];
    }
  }
  return NULL;
}
piece *v_piece_occupying(piece *p, Vector2 coords) {

  for (int i = 0; i < 32; ++i) {
    if (vec_cmp(coords, p[i].coords)) {
      return &p[i];
    }
  }
  return NULL;
}
void drawPieces(piece *p) {
  for (int i = 0; i < 32; ++i) {
    if (p[i].is_dead)
      continue;
    DrawTexture(*piece_to_texture(p[i].piece, p[i].side), p[i].coords.x + 10,
                p[i].coords.y, p->side == CWHITE ? WHITE : BLACK);
  }
  // for(int i = 0; i < 8; ++i){
  //   DrawTexture(wpawn, p[i].x+10,p[i].y, WHITE );
  //   DrawTexture(bpawn, p[i+8].x+10, p[i+8].y, BLACK);
  // }
}
void loadPieces() {
  i_wpawn = LoadImage("pieces/WP.png");
  i_bpawn = LoadImage("pieces/BP.png");

  i_wknight = LoadImage("pieces/WN.png");
  i_bknight = LoadImage("pieces/BN.png");

  i_wbishop = LoadImage("pieces/WB.png");
  i_bbishop = LoadImage("pieces/BB.png");

  i_wrook = LoadImage("pieces/WR.png");
  i_brook = LoadImage("pieces/BR.png");

  i_wqueen = LoadImage("pieces/WQ.png");
  i_bqueen = LoadImage("pieces/BQ.png");

  i_wking = LoadImage("pieces/WK.png");
  i_bking = LoadImage("pieces/BK.png");
  // ImageResize(&i_wpawn, 100, 100);
  // ImageResize(&i_bpawn, 100, 100);
  // ImageResize(&i_bknight, 100, 100);
  // ImageResize(&i_wknight, 100, 100);
  // ImageResize(&i_wbishop, 100, 100);
  // ImageResize(&i_bbishop, 100, 100);
  // ImageResize(&i_wrook, 100, 100);
  // ImageResize(&i_brook, 100, 100);
  Image **p_images = i_pieces;
  for (; *p_images != NULL; ++p_images) {
    ImageResize(*p_images, 100, 100);
  }
  wpawn = LoadTextureFromImage(i_wpawn);
  bpawn = LoadTextureFromImage(i_bpawn);
  wknight = LoadTextureFromImage(i_wknight);
  bknight = LoadTextureFromImage(i_bknight);
  wbishop = LoadTextureFromImage(i_wbishop);
  bbishop = LoadTextureFromImage(i_bbishop);
  wrook = LoadTextureFromImage(i_wrook);
  brook = LoadTextureFromImage(i_brook);
  wqueen = LoadTextureFromImage(i_wqueen);
  bqueen = LoadTextureFromImage(i_bqueen);
  wking = LoadTextureFromImage(i_wking);
  bking = LoadTextureFromImage(i_bking);
}

void unloadPieces() {
  Texture2D **tex = textures;

  for (; *tex != NULL; ++tex) {
    UnloadTexture(**tex);
  }

  free(textures);

  Image **ptr = i_pieces;

  for (; *ptr != NULL; ++ptr) {
    UnloadImage(**ptr);
  }

  free(i_pieces);
}
// bool is_blocked(piece *p, const char source, const char *dest)
// {

// }
bool is_blocked(piece *p, const char *addr1, const char *addr2) {
  if (p->piece == KNIGHT) {
    return false; // knights can never be blocked duh
  }
  // else if(p->piece == PAWN){
  //   //NOTE: Case for pawn is checked in move() //huh?
  // }
  if (strlen(addr1) != 2 && strlen(addr2) != 2) {
    puts("Wrong length for addr");
    exit(1);
  }
  // vector *ret = malloc(sizeof(vector*));
  // v_new(ret);
  int limit;
  char template[3];
  if (strcmp(addr1, addr2) == 0) { // same square
    puts("Same addr");
    exit(1);
  }
  if (p->piece == ROOK) {
    if (*addr1 == *addr2) { // same 'first' char in address
      // puts("E");
      limit = addr1[1] - addr2[1]; //how many cells to check
      char addr[3];
      strcpy(addr, limit < 0 ? addr1 : addr2); //what is the lower?
      for (int i = 1; i < abs(limit); ++i) {
        addr[1]++; // hwah?
        piece *ptr = piece_occupying(pieces, addr);
        if (ptr != NULL)
          return true;
      }

    } else if (addr1[1] == addr2[1]) { // same 'second' char in address
      //NOTE: Comments on the procedure above also describe what this conditional block does
      // puts("D");
      limit = addr1[0] - addr2[0];
      char addr[3];
      strcpy(addr, limit < 0 ? addr1 : addr2);
      piece *ptr;
      for (int i = 1; i < abs(limit); ++i) {
        addr[0]++;
        ptr = piece_occupying(pieces, addr);
        if (ptr != NULL)
          return true;
        // printf("%s\n",addr);
      }
    }
  } else if (p->piece == BISHOP) { // BISHOP

    strcpy(template, addr1);
    bool add_f = false, add_b = false;
    if (*template <*addr2) {
      add_f = true;
    } else
      ;
    if (template[1] < addr2[1])
      add_b = true;
    else
      ;
    piece *ptr;

    while (*template != *addr2) {

      add_f ? ++*template : --*template,
          add_b ? ++template[1] : --template[1]; // printf("%s\n", template);

      printf("%s\n", template);
      if (strcmp(template, addr2) == 0)
        continue;
      ptr = piece_occupying(pieces, template);

      if (ptr != NULL) {
        return true;
      }
    }
    return false;

  } else if (p->piece == PAWN) { // PAWN

    char max = addr1[1] < addr2[1] ? addr2[1] : addr1[1];
    char min = addr1[1] < addr2[1] ? addr1[1] : addr2[1];

    *template = *addr1;
    template[1] = min;
    template[2] = '\0';

    for (; template[1] <= max; ++template[1]) {

      // printf("%s\n", template);
      if (strcmp(template, addr1) == 0)
        ;
      else if (is_occupied(p, template))
        return true;
    }
  } else if (p->piece == QUEEN) {


    //COPY PASTED CODE FROM ROOK MOVEMENT
    if (*addr1 == *addr2) { // same 'first' char in address
      // puts("E");
      limit = addr1[1] - addr2[1];
      char addr[3];
      strcpy(addr, limit < 0 ? addr1 : addr2);
      for (int i = 1; i < abs(limit); ++i) {
        addr[1]++; // hwah?
        piece *ptr = piece_occupying(pieces, addr);
        if (ptr != NULL)
          return true;
      }

    } else if (addr1[1] == addr2[1]) { // same 'first' char in address
      // puts("D");
      limit = addr1[0] - addr2[0];
      char addr[3];
      strcpy(addr, limit < 0 ? addr1 : addr2);
      piece *ptr;
      for (int i = 1; i < abs(limit); ++i) {

        addr[0]++;
        ptr = piece_occupying(pieces, addr);
        if (ptr != NULL)
          return true;
        // printf("%s\n",addr);
      }
      
    } 
    //COPY PASTED CODE FROM BISHOP MOVEMENT BELOW
    else { 

      strcpy(template, addr1);
      bool add_f = false, add_b = false;
      if (*template <*addr2) {
        add_f = true;
      } else
        ;
      if (template[1] < addr2[1])
        add_b = true;
      else
        ;
      piece *ptr;

      while (*template != *addr2) {

        add_f ? ++*template : --*template,
            add_b ? ++template[1] : --template[1]; // printf("%s\n", template);

        printf("%s\n", template);
        if (strcmp(template, addr2) == 0)
          continue;
        ptr = piece_occupying(pieces, template);

        if (ptr != NULL) {
          return true;
        }
      }
      return false;
    }
  }
  return false;
}
