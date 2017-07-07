#pragma once
#pragma warning(disable :4577)
#pragma warning(disable :4530)
#include <stdint.h>
#include <sdl\SDL.h>

enum Colour { WHITE, BLACK };
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum GameState { MAINMENU, PLAYING, CHECKMATE, OPTIONS };
//enum Button { NEWGAME, EXIT, OPTIONS, RESUME, NONE};

extern int board120to64[120];

void initBoard120to64();
bool isValidTile(int position120);

