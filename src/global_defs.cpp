#include "global_defs.h"

int board120to64[120];

void initBoard120to64()
{
	for(int i = 0; i < 120; i++)
	{
		board120to64[i] = 120;
	}

	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			board120to64[ 21 + x + 10*y ] = 8*y + x;
		}
	}
}


bool isValidTile(int position120)
{
	return ( board120to64[position120]<64 && board120to64[position120] >= 0)
	       ? true : false;	
}

