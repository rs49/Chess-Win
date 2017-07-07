#include "game.h"
#include "global_init.h"
//#include "piece.h"
//#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

void Game::newGame()
{
	mGameState = PLAYING;
	mBoard.clearBoard();
	newBoard();

}

void Game::newBoard()
{
	mBoard.addPiece(21, WHITE, ROOK, true);
	mBoard.addPiece(22, WHITE, KNIGHT, true);
	mBoard.addPiece(23, WHITE, BISHOP, true);
	mBoard.addPiece(24, WHITE, QUEEN, true);
	mBoard.addPiece(25, WHITE, KING, true);
	mBoard.addPiece(26, WHITE, BISHOP, true);
	mBoard.addPiece(27, WHITE, KNIGHT, true);
	mBoard.addPiece(28, WHITE, ROOK, true);

	for (int i = 31; i< (31+8); i++)
	{
		mBoard.addPiece(i, WHITE, PAWN, true);
	}


	mBoard.addPiece(91, BLACK, ROOK, true);
	mBoard.addPiece(92, BLACK, KNIGHT, true);
	mBoard.addPiece(93, BLACK, BISHOP, true);
	mBoard.addPiece(94, BLACK, QUEEN, true);
	mBoard.addPiece(95, BLACK, KING, true);
	mBoard.addPiece(96, BLACK, BISHOP, true);
	mBoard.addPiece(97, BLACK, KNIGHT, true);
	mBoard.addPiece(98, BLACK, ROOK, true);

	for (int i = 81; i< (81+8); i++)
	{
		mBoard.addPiece(i, BLACK, PAWN, true);
	}

	mBoard.setCurrPlayer(WHITE);
	mSelectedTile = 120;
	mSelectedPiece = 0;

}

void Game::selectTile(int position)
{
	// If the same tile is selected, turn it off
	if(position == mSelectedTile)
	{
		position = 120;
		mSelectedPiece =0;
	}
	else if(mSelectedPiece)
	{
		list<Piece*> playerPieces;
		list<Piece*>::iterator piece_it;

		(mBoard.getCurrPlayer() == WHITE)
		? playerPieces = mBoard.getWhitePieces() :
		  playerPieces = mBoard.getBlackPieces();
		
		// find the piece
		for(piece_it=playerPieces.begin(); piece_it != playerPieces.end(); piece_it++)
		{
			if( board120to64[ (*piece_it)->getPosition() ] == mSelectedTile)
			{
				list<uint32_t>::iterator move_it;
				list<uint32_t> moveList = (*piece_it)->getLegalMoves(&mBoard);

				for(move_it=moveList.begin(); move_it != moveList.end(); move_it++)
				{
					if( board120to64[ ((*move_it)>>7)&0x7f ] == position)
					{
						mBoard.movePiece(*move_it);
						position = 120;
						mSelectedPiece = 0;
						break;
					}
				}
			}
		}
	}
	

	mSelectedTile = position;

	if(mBoard.isWhitePiece(position))
	{
		mSelectedPiece = 1;
	
	}
	else if (mBoard.isBlackPiece(position))
	{
		mSelectedPiece = 1;
	}
	else
	{
		mSelectedPiece = 0;
	}
}

void Game::drawBoard(int mouseX, int mouseY)
{
	SDL_SetRenderDrawColor(renderer, 255, 244, 142, 0);
	SDL_RenderClear(renderer);

	SDL_Rect tile = { 0, 0, TILE_SIZE, TILE_SIZE};

	// Draw tiled board

	for(int i = 0; i < 64; i++)
	{
		tile.x = TILE_SIZE * (i%8);

		tile.y = TILE_SIZE * (7-i/8);
		if( mSelectedTile == i)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

		}
		else if(tile_colour[i] == 0)
		{
			SDL_SetRenderDrawColor(renderer, 162, 103, 0, 0);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		}

		SDL_RenderFillRect(renderer, &tile);
	}

	// draw moves for potential moves
	list<Piece*>::iterator it;
	list<Piece*> currList;

	list<uint32_t> moveList;
	list<uint32_t>::iterator move_it;
	int position64;
	
	if(mSelectedPiece)
	{
		SDL_SetRenderDrawColor(renderer, 50, 50, 200, 0);

		(mBoard.getCurrPlayer() == WHITE)
		? currList = mBoard.getWhitePieces() :
		  currList = mBoard.getBlackPieces();

		for(it = currList.begin(); it != currList.end(); it++)
		{
			if( board120to64[ (*it)->getPosition() ] == mSelectedTile )
			{
				moveList = (*it)->getLegalMoves(&mBoard);
				break;
			}
		}

		for(move_it = moveList.begin(); move_it != moveList.end(); move_it++)
		{
			position64 = board120to64[  ((*move_it)>>7)&0x7f ];

			tile.x = TILE_SIZE*(position64%8);
			tile.y = TILE_SIZE*(7-position64/8);

			
			
			SDL_SetRenderDrawColor(renderer, 50, 50, 200, 0);
			SDL_RenderFillRect(renderer, &tile);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &tile);
			
			//SDL_RenderCopy(renderer, mBlueDotTexture, NULL, &tile);


		}
	}
	
	//draw the pieces on the board
	
	currList = mBoard.getWhitePieces();
	for( it=currList.begin(); it != currList.end(); it++ )
	{
		drawPiece( (*it)->getColour(), (*it)->getPieceType(), (*it)->getPosition() );
	}

	currList = mBoard.getBlackPieces();
	for( it=currList.begin(); it != currList.end(); it++ )
	{
		drawPiece( (*it)->getColour(), (*it)->getPieceType(), (*it)->getPosition() );
	}
	


	SDL_Rect renderQuad = { 500, 10, 120, 60 };

	// Draw if it is check or checkmate
	if (mBoard.isCurrPlayerInCheckmate())
	{
		mGameState = CHECKMATE;
		renderQuad.y = 100;
		SDL_RenderCopy(renderer, mCheckmateTexture, NULL, &renderQuad) ;

		(isPointInsideBox(mouseX, mouseY, mPlaying_NewGame))
		? SDL_RenderCopy(renderer, mNewGameTexture_mouseover, NULL, &mPlaying_NewGame) :
		  SDL_RenderCopy(renderer, mNewGameTexture, NULL, &mPlaying_NewGame);


	}
	else
	{	
		if (mBoard.getCurrPlayer() == WHITE)
			SDL_RenderCopy(renderer, mWhiteTurnTexture, NULL, &renderQuad) ;
		else
			SDL_RenderCopy(renderer, mBlackTurnTexture, NULL, &renderQuad) ;
		
		renderQuad.y = 200;
		if(mBoard.isCurrPlayerInCheck())
		{
			SDL_RenderCopy(renderer, mCheckTexture, NULL, &renderQuad) ;
		}
	}

	(isPointInsideBox(mouseX, mouseY, mPlaying_Options))
	? SDL_RenderCopy(renderer, mGearTexture_mouseover, NULL, &mPlaying_Options) :
	  SDL_RenderCopy(renderer, mGearTexture, NULL, &mPlaying_Options);


	

	
	SDL_RenderPresent(renderer);


}

void Game::drawPiece(Colour colour, PieceType pieceType, int position120)
{
	int x, y, position64;

	position64 = board120to64[position120];

	x = position64%8;
	y = 7-position64/8;

	SDL_Rect renderQuad = { x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE };

	switch(pieceType)
	{
		case PAWN:
			{
				(colour == WHITE)
				? SDL_RenderCopy(renderer, mWhitePawnTexture, NULL, &renderQuad) :
				  SDL_RenderCopy(renderer, mBlackPawnTexture, NULL, &renderQuad);

				break;
				  
			}
		case KNIGHT:
			{
				(colour == WHITE)
				? SDL_RenderCopy(renderer, mWhiteKnightTexture, NULL, &renderQuad) :
				  SDL_RenderCopy(renderer, mBlackKnightTexture, NULL, &renderQuad);

				break;
				  
			}
		case BISHOP:
			{
				(colour == WHITE)
				? SDL_RenderCopy(renderer, mWhiteBishopTexture, NULL, &renderQuad) :
				  SDL_RenderCopy(renderer, mBlackBishopTexture, NULL, &renderQuad);

				break;
				  
			}
		case ROOK:
			{
				(colour == WHITE)
				? SDL_RenderCopy(renderer, mWhiteRookTexture, NULL, &renderQuad) :
				  SDL_RenderCopy(renderer, mBlackRookTexture, NULL, &renderQuad);

				break;
				  
			}
		case QUEEN:
			{
				(colour == WHITE)
				? SDL_RenderCopy(renderer, mWhiteQueenTexture, NULL, &renderQuad) :
				  SDL_RenderCopy(renderer, mBlackQueenTexture, NULL, &renderQuad);

				break;
				  
			}
		case KING:
			{
				(colour == WHITE)
				? SDL_RenderCopy(renderer, mWhiteKingTexture, NULL, &renderQuad) :
				  SDL_RenderCopy(renderer, mBlackKingTexture, NULL, &renderQuad);

				break;
				  
			}
	}
}

void Game::initAssets()
{
	loadTexture(&mWhitePawnTexture,"60_png/WhitePawn.png");
	loadTexture(&mWhiteKnightTexture,"60_png/WhiteKnight.png");
	loadTexture(&mWhiteBishopTexture,"60_png/WhiteBishop.png");
	loadTexture(&mWhiteRookTexture,"60_png/WhiteRook.png");
	loadTexture(&mWhiteQueenTexture,"60_png/WhiteQueen.png");
	loadTexture(&mWhiteKingTexture,"60_png/WhiteKing.png");

	loadTexture(&mBlackPawnTexture,"60_png/BlackPawn.png");
	loadTexture(&mBlackKnightTexture,"60_png/BlackKnight.png");
	loadTexture(&mBlackBishopTexture,"60_png/BlackBishop.png");
	loadTexture(&mBlackRookTexture,"60_png/BlackRook.png");
	loadTexture(&mBlackQueenTexture,"60_png/BlackQueen.png");
	loadTexture(&mBlackKingTexture,"60_png/BlackKing.png");

	loadTexture(&mWhiteTurnTexture,"buttons/whiteturn.png");
	loadTexture(&mBlackTurnTexture,"buttons/blackturn.png");

	loadTexture(&mCheckTexture,"buttons/check.png");
	loadTexture(&mCheckmateTexture,"buttons/checkmate.png");

	loadTexture(&mNewGameTexture,"buttons/newGame.png");
	loadTexture(&mNewGameTexture_mouseover,"buttons/newGame_mouseover.png");
	loadTexture(&mExitTexture,"buttons/exit.png");
	loadTexture(&mExitTexture_mouseover,"buttons/exit_mouseover.png");
	loadTexture(&mResumeTexture,"buttons/resume.png");
	loadTexture(&mResumeTexture_mouseover,"buttons/resume_mouseover.png");

	loadTexture(&mGearTexture,"buttons/gear.png");
	loadTexture(&mGearTexture_mouseover,"buttons/gear_mouseover.png");

	loadTexture(&mLogoTexture,"buttons/logo.png");
	loadTexture(&mAuthorTexture,"buttons/author.png");


	// main menu - new game coordinates
	SDL_Rect button;

	button.x = 640/2 - 60;
	button.y = 200;
	button.w = 120;
	button.h = 50;

	mMainMenu_NewGame = button;

	
	 
	// main menu - exit coordinate
	button.y = 300;
	mMainMenu_Exit = button;

	// options menu - resume coordinates
	button.y = 100;
	mOptions_Resume = button;

	// playing - after checkmate
	
	button.x = 500;
	button.y = 10;
	mPlaying_NewGame = button;

	// while playing - gear coordinate
	button.x = 590;
	button.y = 430;
	button.w = 40;
	button.h = 40;

	mPlaying_Options = button;


}

void Game::loadTexture(SDL_Texture **targetTexture, string pathName)
{
	SDL_Surface *surface = IMG_Load(pathName.c_str());
	if(surface == NULL)
	{
		printf("Failed load surface\n");
	}
	
	*targetTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if( targetTexture == NULL )
	{
		printf("Failed loading texture: %s\n%s\n", pathName.c_str(), SDL_GetError());
	}
}

void Game::drawMainMenu(int mouseX, int mouseY)
{
	SDL_Rect renderQuad;
	renderQuad.x = 640/2-100;
	renderQuad.y = 20;
	renderQuad.w = 200;
	renderQuad.h = 100;

	SDL_SetRenderDrawColor(renderer, 255, 244, 142, 0);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, mLogoTexture, NULL, &renderQuad);

	renderQuad.x = 0;
	renderQuad.y = 430;
	renderQuad.w = 200;
	renderQuad.h = 50;
	
	SDL_RenderCopy(renderer, mAuthorTexture, NULL, &renderQuad);



	(isPointInsideBox(mouseX, mouseY, mMainMenu_NewGame))
	? SDL_RenderCopy(renderer, mNewGameTexture_mouseover, NULL, &mMainMenu_NewGame) :
	  SDL_RenderCopy(renderer, mNewGameTexture, NULL, &mMainMenu_NewGame);

	(isPointInsideBox(mouseX, mouseY, mMainMenu_Exit))
	? SDL_RenderCopy(renderer, mExitTexture_mouseover, NULL, &mMainMenu_Exit) :
	  SDL_RenderCopy(renderer, mExitTexture, NULL, &mMainMenu_Exit);

	SDL_RenderPresent(renderer);
}

void Game::drawOptionsMenu(int mouseX, int mouseY)
{
	SDL_SetRenderDrawColor(renderer, 255, 244, 142, 0);
	SDL_RenderClear(renderer);

	(isPointInsideBox(mouseX, mouseY, mOptions_Resume))
	? SDL_RenderCopy(renderer, mResumeTexture_mouseover, NULL, &mOptions_Resume) :
	  SDL_RenderCopy(renderer, mResumeTexture, NULL, &mOptions_Resume) ;


	(isPointInsideBox(mouseX, mouseY, mMainMenu_NewGame))
	? SDL_RenderCopy(renderer, mNewGameTexture_mouseover, NULL, &mMainMenu_NewGame) :
	  SDL_RenderCopy(renderer, mNewGameTexture, NULL, &mMainMenu_NewGame);

	(isPointInsideBox(mouseX, mouseY, mMainMenu_Exit))
	? SDL_RenderCopy(renderer, mExitTexture_mouseover, NULL, &mMainMenu_Exit) :
	  SDL_RenderCopy(renderer, mExitTexture, NULL, &mMainMenu_Exit);

	SDL_RenderPresent(renderer);
}


bool Game::isPointInsideBox(int x, int y, SDL_Rect box)
{
	if( (x > box.x) &&
		( x < (box.x+box.w) ) &&
		 ( y > box.y ) &&
		 ( y < (box.y+box.h) ) )
	{
		return true;
	}

	return false;
}

void Game::mouseButtonEvent(int mouseX, int mouseY)
{
	if (mGameState == MAINMENU)
	{
		if(isPointInsideBox(mouseX, mouseY, mMainMenu_NewGame))
		{
			newGame();
		}
		if(isPointInsideBox(mouseX, mouseY, mMainMenu_Exit))
		{
			run = 0;
		}
	}
	else if (mGameState == PLAYING)
	{
		if(isPointInsideBox(mouseX, mouseY, mPlaying_Options))
		{
			mGameState = OPTIONS;
		}

	}
	else if (mGameState == CHECKMATE)
	{
		if(isPointInsideBox(mouseX, mouseY, mPlaying_NewGame))
		{
			newGame();
		}

		if(isPointInsideBox(mouseX, mouseY, mPlaying_Options))
		{
			mGameState = OPTIONS;
		}
	}

	else if (mGameState == OPTIONS)
	{
		if(isPointInsideBox(mouseX, mouseY, mOptions_Resume))
		{
			mGameState = PLAYING;
		}
		if(isPointInsideBox(mouseX, mouseY, mMainMenu_NewGame))
		{
			newGame();
		}
		if(isPointInsideBox(mouseX, mouseY, mMainMenu_Exit))
		{
			run = 0;
		}

	}


}

GameState Game::getGameState()
{
	return mGameState;
}
