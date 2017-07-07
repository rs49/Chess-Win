#pragma once

#include "piece.h"

class King : public Piece
{
	private:
		const int direction[8] = { -11, -10, -9, -1, 1, 9, 10, 11};

	public:
		King(int position120, Colour colour, bool firstMove);
		list<uint32_t> getPotentialMoves(GameBitBoard gameBitBoard);
};
