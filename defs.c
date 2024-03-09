#include "defs.h"
#include "board.h"
#include "pieces.h"
pos **board;
piece *pieces;
Image i_wpawn, i_bpawn, i_wknight, i_bknight, i_wbishop, i_bbishop, i_wrook, i_brook, i_wqueen, i_bqueen, i_wking, i_bking;
Image **i_pieces;
Texture2D wpawn, bpawn, wknight, bknight, wbishop, bbishop, wrook, brook, wqueen, bqueen, wking, bking;
Texture2D **textures;
piece_lock lock;
piece *active_piece;
