#pragma once

#include "piece.h"

class Pawn : public Piece
{
	private:
		const int direction = 10;

	public:
		Pawn(int direction120, Colour colour, bool firstMove);
		list<uint32_t> getPotentialMoves(GameBitBoard gameBitBoard);
};
