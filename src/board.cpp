#include "board.h"

#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

list<Piece*> Board::getWhitePieces()
{
	return mWhitePieces;
}

list<Piece*> Board::getBlackPieces()
{
	return mBlackPieces;
}

void Board::addPiece(int position120, Colour colour, PieceType pieceType, bool firstMove)
{
	switch(pieceType)
	{
		case PAWN:
			{
				
				(colour == WHITE) 
				? mWhitePieces.push_back(new Pawn(position120, WHITE, firstMove)) :
				  mBlackPieces.push_back(new Pawn(position120, BLACK, firstMove));
				
				break;
			}
		case KNIGHT:
			{
				
				(colour == WHITE) 
				? mWhitePieces.push_back(new Knight(position120, WHITE, firstMove)) :
				  mBlackPieces.push_back(new Knight(position120, BLACK, firstMove));
				
				break;
			}
		case BISHOP:
			{
				
				(colour == WHITE) 
				? mWhitePieces.push_back(new Bishop(position120, WHITE, firstMove)) :
				  mBlackPieces.push_back(new Bishop(position120, BLACK, firstMove));
				
				break;
			}
		case ROOK:
			{
				
				(colour == WHITE) 
				? mWhitePieces.push_back(new Rook(position120, WHITE, firstMove)) :
				  mBlackPieces.push_back(new Rook(position120, BLACK, firstMove));
				
				break;
			}
		case QUEEN:
			{
				
				(colour == WHITE) 
				? mWhitePieces.push_back(new Queen(position120, WHITE, firstMove)) :
				  mBlackPieces.push_back(new Queen(position120, BLACK, firstMove));
				
				break;
			}
		case KING:
			{
				
				(colour == WHITE) 
				? mWhitePieces.push_back(new King(position120, WHITE, firstMove)) :
				  mBlackPieces.push_back(new King(position120, BLACK, firstMove));
				
				break;
			}

	}

	mGameBitBoard.update(mWhitePieces, mBlackPieces, 120);

	
}

void Board::clearBoard()
{
	list<Piece*>::iterator piece_it;
	
	for(piece_it=mWhitePieces.begin(); piece_it != mWhitePieces.end(); piece_it++)
	{
		delete *piece_it;
		mWhitePieces.erase(piece_it);
	}

	for(piece_it=mBlackPieces.begin(); piece_it != mBlackPieces.end(); piece_it++)
	{
		delete *piece_it;
		mWhitePieces.erase(piece_it);
	}

	mCurrPlayerInCheck = false;
	mCurrPlayerInCheckmate = false;


}

void Board::removePiece(int position120)
{
	list<Piece*> *playerPieces;
	list<Piece*>::iterator piece_it;

	int position64 = board120to64[position120];

	mGameBitBoard.isWhitePiece(position64) ? 
		playerPieces = &mWhitePieces : playerPieces = &mBlackPieces;

	for(piece_it=playerPieces->begin(); piece_it != playerPieces->end(); piece_it++)
	{
		if ( (*piece_it)->getPosition() == position120 )
		{
			delete *piece_it;
			playerPieces->erase(piece_it);
			break;
		}
	}

	mGameBitBoard.update(mWhitePieces, mBlackPieces, 0);

}

void Board::movePiece(uint32_t move)
{
	uint32_t startPos = (move & 0x7f);
	uint32_t destPos = ((move>>7) & 0x7f);

	int enPas = 120;

	list<Piece*> playerPieces;
	list<Piece*>::iterator piece_it;

	mCurrPlayer == WHITE ? 
		playerPieces = getWhitePieces() : playerPieces = getBlackPieces();

	for(piece_it = playerPieces.begin(); piece_it !=playerPieces.end(); piece_it++)
	{
		if( (*piece_it)->getPosition() == startPos)
		{
			if( (*piece_it)->isFirstMove() )
			{
				(*piece_it)->setFirstMoveFalse();
			}

			if ( (move>>15) & 1 )
			{
				enPas = (move>>16) & 0x7f;	
				mEnPasPawn120 = (move>>7)&0x7f;
				
			}
						
			if ((move >> 14) & 1)
			{
				removePiece(destPos);
			}

			if ((move >> 23) & 1)
			{
				removePiece(mEnPasPawn120);
			}

			(*piece_it)->setPosition(destPos);

			mGameBitBoard.update(mWhitePieces, mBlackPieces, enPas);

			if(isPlayerAttackingKing(mCurrPlayer,mGameBitBoard))
			{
				mCurrPlayerInCheck = true;
				//printf("Check");
			}
			else
			{
				mCurrPlayerInCheck = false;
			}

			mCurrPlayer == WHITE ? mCurrPlayer = BLACK : mCurrPlayer = WHITE;

			if(isCurrPlayerInCheckmate())
			{
				//printf("checkmate\n");
			}
			break;
		}
	}

}

Colour Board::getCurrPlayer()
{
	return mCurrPlayer;
}

void Board::setCurrPlayer(Colour colour)
{
	mCurrPlayer = colour;
}

GameBitBoard Board::getGameBitBoard()
{
	return mGameBitBoard;
}

bool Board::isWhitePiece(int position64)
{
	return mGameBitBoard.isWhitePiece(position64);
}

bool Board::isBlackPiece(int position64)
{
	return mGameBitBoard.isBlackPiece(position64);
}

bool Board::isCurrPlayerInCheck()
{
	return mCurrPlayerInCheck;
}

bool Board::isCurrPlayerInCheckmate()
{
	list<Piece*> playerPieces;

	list<Piece*>::iterator it;

	(mCurrPlayer == WHITE)
	? playerPieces = getWhitePieces() : playerPieces = getBlackPieces();

	list<uint32_t> moveList;
	list<uint32_t>::iterator move_it;

	for(it=playerPieces.begin(); it != playerPieces.end(); it++)
	{
		moveList = (*it)->getLegalMoves(this);
		if (moveList.size() > 0)
		{
			return false;
		}
		//printf("checking player Pieces\n");

	}

	mCurrPlayerInCheckmate = true;

	return true;}

Piece Board::getPieceAtPosition(int position120)
{
	list<Piece*> *playerPieces;
	list<Piece*>::iterator it;

	int position64=board120to64[position120];

	(mGameBitBoard.isWhitePiece(position64))
	? playerPieces = &mWhitePieces : playerPieces = &mBlackPieces ;

	for(it=playerPieces->begin(); it != playerPieces->end(); it++)
	{
		if ( (*it)->getPosition() == position120 )
		{
			return (**it);
		}
	}

	return (**it);

}

bool Board::isPlayerAttackingKing(Colour colour, GameBitBoard testBoard)
{
	list<Piece*> playerPieces;
	list<Piece*> otherPlayerPieces;

	list<Piece*>::iterator it;

	list<uint32_t> moveList;
	list<uint32_t>::iterator move_it;

	uint32_t kingPosition120;


	if(colour == WHITE)
	{
		playerPieces = getWhitePieces();
		kingPosition120 = testBoard.getBlackKing();
	}
	else
	{
		playerPieces = getBlackPieces();
		kingPosition120 = testBoard.getWhiteKing();

	}



	for(it=playerPieces.begin(); it != playerPieces.end(); it++)
	{
		moveList = (*it)->getPotentialMoves(testBoard);
		//printf("checking player Pieces\n");

		for (move_it = moveList.begin(); move_it != moveList.end(); move_it++)
		{
			if (*move_it>>14==1) //check if it is attacking move
			{
				//printf("checking attacking move: %d\t king at: %d\n",((*move_it>>7) & 0x7f), kingPosition120);
				if( ((*move_it>>7) & 0x7f) == kingPosition120)
				{
					return true;
				}
			}
		}
	}


	return false;

}

