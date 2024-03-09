#ifndef _PIECES_H
#define _PIECES_H 1
#include <raylib.h>
#include "board.h"


extern void initPieces(piece *p);
extern void init_references();
extern void drawPieces(piece *p);
extern void loadPieces();
extern void unloadPieces();
extern void unloadDefsPieces();
extern bool is_occupied(piece *p, char *location);
extern void p_inherit_pos(piece *p, pos *b);
extern char *name_piece_occupying(piece*p, char *location);

// #define piece_occupying(x) _Generic((x), char*:c_piece_occupying, int: i_piece_occupying, Vector2: v_piece_occupying, other:err);
extern piece *piece_occupying(piece *p, char *location);
extern piece *i_piece_occupying(piece *p, int x, int y);
extern piece *v_piece_occupying(piece *p, Vector2 coords);
extern bool is_blocked(piece *p, const char *addr1, const char *addr2);
extern piece *pieces;
extern Image i_wpawn, i_bpawn, i_wknight, i_bknight, i_wbishop, i_bbishop, i_wrook, i_brook, i_wqueen, i_bqueen, i_wking, i_bking;
extern Image **i_pieces;
extern Texture2D wpawn, bpawn, wknight, bknight, wbishop, bbishop, wrook, brook, wqueen, bqueen, wking, bking;
extern Texture2D **textures;
#endif
