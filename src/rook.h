#pragma once

#include "piece.h"

class Rook : public Piece
{
	private:
		const int direction[4] = {-10, -1, 1, 10};

	public:
		Rook(int position120, Colour colour, bool firstMove);
		list<uint32_t> getPotentialMoves(GameBitBoard gameBitBoard);
};

