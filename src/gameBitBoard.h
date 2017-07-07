#pragma once

#include "piece.h"

class GameBitBoard
{
	private:
		uint64_t mWhiteBitBoard;
		uint64_t mBlackBitBoard;
		uint64_t mBothBitBoards;
		int mWhiteKingPosition120;
		int mBlackKingPosition120;
		int mEnPas;
		int mEnPasPawn120;

	public:
		void update(list<Piece*> whitePieces, list<Piece*> blackPieces, int enpas);
		bool isTileFree(int position64);
		bool isWhitePiece(int position64);
		bool isBlackPiece(int position64);
		int getWhiteKing();
		int getBlackKing();
		int getEnPas();
		void setEnPas(int square120);
		void moveUpdateBitBoard(Colour colour, uint32_t move);

};

