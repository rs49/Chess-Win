#pragma once

#include "piece.h"

class Knight : public Piece
{
	private:
		const int direction[8] = {-21, -19, -12, -8, 8, 12, 19, 21};

	public:
		Knight(int position120, Colour colour, bool firstMove);
		list<uint32_t> getPotentialMoves(GameBitBoard gameBitBoard);
};
