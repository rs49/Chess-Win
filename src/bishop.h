#pragma once

#include "piece.h"

class Bishop : public Piece
{
	private:
		const int direction[4] = {-11, -9, 9, 11};

	public:
		Bishop(int position120, Colour colour, bool firstMove);
		list<uint32_t> getPotentialMoves(GameBitBoard gameBitBoard);

};
