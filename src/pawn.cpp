#include "pawn.h"
#include "gameBitBoard.h"

Pawn::Pawn(int position120, Colour colour, bool firstMove) :
	Piece(position120, colour, PAWN, firstMove)
{
}
/*
 * move structure:
 * bits 0-6: 	the inital position.
 * bits 7-13: 	the destination position.
 * bit 	14: 	determines if it is capturing an enemy piece.
 * bit	15:	determines if the move is a pawn jump.
 * bits	16-22: 	The En Passant square.
 * bit	23:	determines if the move is an En Passant capture
 *
 * Attacking moves are at the begining of the list and passive (non-capturing)
 * moves are at the end of the list. This is for future AI.
 */

list<uint32_t> Pawn::getPotentialMoves(GameBitBoard gameBitBoard)
{
	list<uint32_t> moves;

	int testDirection;

	int testTile;
	int testTile64;

	uint32_t moveToAdd = uint32_t(getPosition());

	getColour() == WHITE ? testDirection = direction : testDirection=direction*-1;

	testTile = getPosition()+testDirection;
	testTile64 = board120to64[testTile];

	if(isValidTile(testTile))
	{
		if(gameBitBoard.isTileFree(testTile64))
		{	
			moves.push_back(moveToAdd | (testTile<<7));
		}
		
	}

	int enPas120;

	if (isFirstMove())
	{
		testTile = testTile+testDirection;
		testTile64 = board120to64[testTile];

		if(isValidTile(testTile))
		{
			if(gameBitBoard.isTileFree(testTile64))
			{
				enPas120 = getPosition() + testDirection;	
				moveToAdd |= uint32_t(1)<<15;
				moveToAdd |= (enPas120 << 16);
				moves.push_front(moveToAdd | (testTile<<7));
			}
			
		}
	}

	
	int attack_dir[2] = {9, 11};
	int board_dir;
	getColour() == WHITE ? board_dir = 1 : board_dir = -1;


	for (int i = 0; i < sizeof(attack_dir)/sizeof(attack_dir[0]); i++)
	{
		moveToAdd = uint32_t(getPosition());
		testTile = getPosition()+attack_dir[i]*board_dir;
		testTile64 = board120to64[testTile];
		if(isValidTile(testTile))
		{

			if(~gameBitBoard.isTileFree(testTile64))
			{
				if (getColour() == WHITE)
				{
					if(gameBitBoard.isBlackPiece(testTile64))
					{
						moveToAdd |= (1<<14);

						moves.push_back(moveToAdd | (testTile<<7));
					}
				}
				else
				{
					if(gameBitBoard.isWhitePiece(testTile64))
					{
						moveToAdd |= (1<<14);

						moves.push_back(moveToAdd | (testTile<<7));
					}
				}

			}
			if( gameBitBoard.getEnPas() == testTile )
			{
				moveToAdd |= (1<<23);

				moves.push_back(moveToAdd | (testTile<<7));


			}
		}



	}
	
	


	return moves;
}

