#include "piece.h"
#include "gameBitBoard.h"
#include "board.h"

Piece::Piece()
{
}

Piece::Piece(int position120, Colour colour, PieceType pieceType, bool firstMove)
{
	mPosition120 = position120;
	mColour = colour;
	mPieceType = pieceType;
	mFirstMove = firstMove;
}

int Piece::getPosition()
{
	return mPosition120;
}

void Piece::setPosition(int position120)
{
	mPosition120 = position120;
}

Colour Piece::getColour()
{
	return mColour;
}

void Piece::setColour(Colour colour)
{
	mColour = colour;
}

PieceType Piece::getPieceType()
{
	return mPieceType;
}

void Piece::setPieceType(PieceType pieceType)
{
	mPieceType = pieceType;
}

bool Piece::isFirstMove()
{
	return mFirstMove;
}

void Piece::setFirstMoveFalse()
{
	mFirstMove = false;
}

void Piece::setFirstMove(bool firstMove)
{
	mFirstMove = firstMove;
}


list<uint32_t> Piece::getPotentialMoves(GameBitBoard gameBitBoard)
{
	list<uint32_t> moves;
	return moves;
}

list<uint32_t> Piece::getLegalMoves(Board *gameBoard)
{
	list<uint32_t> moves = getPotentialMoves(gameBoard->getGameBitBoard());
	list<uint32_t> legalMoves;
	list<uint32_t>::iterator it;
	//Board testBoard = gameBoard;
	GameBitBoard testBitBoard;

	//Piece tempPiece;
	//Piece targetPiece;

	Piece tempPiece;

	for(it = moves.begin(); it != moves.end(); it++)
	{
		if( (*it)>>14 ==1)
		{
			
			Piece targetPiece = gameBoard->getPieceAtPosition( ((*it)>>7)&0x7f );

			tempPiece.setPosition( targetPiece.getPosition() );
			tempPiece.setColour( targetPiece.getColour() );
			tempPiece.setPieceType( targetPiece.getPieceType() );
			tempPiece.setFirstMove( targetPiece.isFirstMove() );

			gameBoard->removePiece( ((*it)>>7)&0x7f  );

			
		}
		testBitBoard = gameBoard->getGameBitBoard();
		testBitBoard.moveUpdateBitBoard(mColour, (*it) );
		
	

		if (mColour == WHITE)
		{
			if( gameBoard->isPlayerAttackingKing(BLACK, testBitBoard) == false)
			{
				legalMoves.push_back( (*it) );
			}
		}
		else
		{
			if( gameBoard->isPlayerAttackingKing(WHITE, testBitBoard) == false)
			{
				legalMoves.push_back( (*it) );
			}

		}
		if( (*it)>>14 ==1)
		{
			//printf("adding %d\n", tempPiece.getPosition());
			gameBoard->addPiece( ((*it)>>7)&0x7f, tempPiece.getColour(), tempPiece.getPieceType() , tempPiece.isFirstMove());
			
		}
	}

	return legalMoves;

}
	
