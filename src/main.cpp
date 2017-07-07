#include <stdio.h>
#include <sdl/SDL.h>
#include "global_init.h"
#include "global_defs.h"


void parseInputs(int mouseX, int mouseY, SDL_Event *e);

//int run = 1;

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Chess",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					640, 480,
					SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	

	initBoard120to64();
	game.initAssets();
	game.newBoard();

	SDL_Event e;

	
	int x, y;

	Uint32 startTick, elapsed;

	while(run)
	{
		startTick = SDL_GetTicks();

		

		SDL_GetMouseState(&x, &y);


		// Parse Inputs/Events
		
		parseInputs(x, y, &e);
	
		// Draw the screen

		if (game.getGameState() == MAINMENU)
		{
			game.drawMainMenu(x,y);
		}
		else if ( (game.getGameState() == PLAYING) || (game.getGameState() == CHECKMATE) )
		{
			game.drawBoard(x,y);	
		}
		else if (game.getGameState() == OPTIONS)
		{
			game.drawOptionsMenu(x, y);
		}


		// Run at 30 frames per second

		elapsed = SDL_GetTicks() - startTick;
		if( elapsed < 33 )
		{
			SDL_Delay( 33 - elapsed );
		}
	}

	return 0;

}

void parseInputs(int mouseX, int mouseY, SDL_Event *e)
{
	while( SDL_PollEvent(e) != 0 )
	{
		if( e->type == SDL_QUIT )
		{
			run = 0;
		}

		else if( e->type == SDL_KEYDOWN )
		{
			switch( e->key.keysym.sym )
			{
				/*case SDLK_q:
					{
						run = 0;
						break;
					}*/
			}
		}
		else if( e->type == SDL_MOUSEBUTTONDOWN )
		{
			if (game.getGameState() == MAINMENU)
			{
				game.mouseButtonEvent(mouseX, mouseY);
			}
			else if (game.getGameState() == OPTIONS)
			{
				game.mouseButtonEvent(mouseX, mouseY);
			}
						
			else if(mouseX<480)
			{
				
				int x = mouseX/TILE_SIZE+1;
				int y = mouseY/TILE_SIZE;
				y = 8-y;

				int position64 = (y-1)*8 + (x-1);
				int position120 = 21 + x + 10*(y-1);

				if( (position120 > 21) && (position120 < 100) )
				{
					game.selectTile(position64);
					//printf("Tile selected: %d\n", position64);
				}
			}
			else
			{
				game.mouseButtonEvent(mouseX, mouseY);
			}
		}

	}

}
