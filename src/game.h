#pragma once

#include "board.h"
#include <sdl/SDL_image.h>
#include <string>

class Game
{
	private:
		Board mBoard;
		int mSelectedTile;
		int mSelectedPiece;

		GameState mGameState = MAINMENU;
		//Button mMouseOver = NONE;
		SDL_Rect mMainMenu_NewGame;
		SDL_Rect mMainMenu_Exit;
		SDL_Rect mPlaying_NewGame;
		SDL_Rect mPlaying_Options;
		SDL_Rect mOptions_Resume;

		SDL_Texture *mWhitePawnTexture;
		SDL_Texture *mWhiteKnightTexture;
		SDL_Texture *mWhiteBishopTexture;
		SDL_Texture *mWhiteRookTexture;
		SDL_Texture *mWhiteQueenTexture;
		SDL_Texture *mWhiteKingTexture;

		SDL_Texture *mBlackPawnTexture;
		SDL_Texture *mBlackKnightTexture;
		SDL_Texture *mBlackBishopTexture;
		SDL_Texture *mBlackRookTexture;
		SDL_Texture *mBlackQueenTexture;
		SDL_Texture *mBlackKingTexture;

		SDL_Texture *mWhiteTurnTexture;
		SDL_Texture *mBlackTurnTexture;

		SDL_Texture *mCheckTexture;
		SDL_Texture *mCheckmateTexture;

		SDL_Texture *mNewGameTexture;
		SDL_Texture *mNewGameTexture_mouseover;
		SDL_Texture *mExitTexture;
		SDL_Texture *mExitTexture_mouseover;
		SDL_Texture *mResumeTexture;
		SDL_Texture *mResumeTexture_mouseover;

		SDL_Texture *mGearTexture;
		SDL_Texture *mGearTexture_mouseover;

		SDL_Texture *mLogoTexture;
		SDL_Texture *mAuthorTexture;


	public:
		void newGame();
		void newBoard();
		void selectTile(int position);
		void drawBoard(int mouseX, int mouseY);
		void drawPiece(Colour colour, PieceType pieceType, int position120);
		void initAssets();
		void loadTexture(SDL_Texture **targetTexture, string pathName);
		void drawMainMenu(int mouseX, int mouseY);
		void drawOptionsMenu(int mouseX, int mouseY);
		bool isPointInsideBox(int x, int y, SDL_Rect box);
		void mouseButtonEvent(int mouseX, int mouseY);
		GameState getGameState();
};
