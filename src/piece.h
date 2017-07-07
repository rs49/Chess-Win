#pragma once

#include "global_defs.h"
#include <list>

using namespace std;

class Board;
class GameBitBoard;

class Piece
{
	private:
		int mPosition120;
		Colour mColour;
		PieceType mPieceType;
		bool mFirstMove;

	public:
		Piece();
		Piece(int position120, Colour colour, PieceType pieceType, bool firstMove);
		int getPosition();
		void setPosition(int position120);
		Colour getColour();
		void setColour(Colour colour);	
		PieceType getPieceType();
		void setPieceType(PieceType pieceType);	
		bool isFirstMove();
		void setFirstMoveFalse();
		void setFirstMove(bool firstMove);			
		virtual list<uint32_t> getPotentialMoves(GameBitBoard gameBitBoard);
		list<uint32_t> getLegalMoves(Board *gameBoard);
};
