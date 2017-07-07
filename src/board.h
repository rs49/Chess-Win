#pragma once

#include "global_defs.h"
#include "piece.h"
#include "gameBitBoard.h"

#include <list>

using namespace std;

class Board
{
	private:
		list<Piece*> mWhitePieces;
		list<Piece*> mBlackPieces;
		Colour mCurrPlayer;
		bool mCurrPlayerInCheck = false;
		bool mCurrPlayerInCheckmate = false;
		GameBitBoard mGameBitBoard;
		int mEnPasPawn120;

	public:
		list<Piece*> getWhitePieces();
		list<Piece*> getBlackPieces();
		void addPiece(int position120, Colour colour, PieceType pieceType, bool firstMove);
		void clearBoard();
		void removePiece(int position120);
		void movePiece(uint32_t move);
		Colour getCurrPlayer();
		void setCurrPlayer(Colour colour);
		GameBitBoard getGameBitBoard();
		bool isWhitePiece(int position64);
		bool isBlackPiece(int position64);
		bool isCurrPlayerInCheck();
		bool isCurrPlayerInCheckmate();
		Piece getPieceAtPosition(int position120);
		bool isPlayerAttackingKing(Colour colour, GameBitBoard testBoard);

};


