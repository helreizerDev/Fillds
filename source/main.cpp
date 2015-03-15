#include <3ds.h>
#include <stdlib.h> 
#include "capp.h"
#include <time.h>

Capp Cgame;

int main()
{
	gfxInitDefault();
    Cgame.init();
	srand (time(NULL));
	while (aptMainLoop() && Cgame.gameState != Cgame.State::Quit)
	{
		gspWaitForVBlank(); 
		Cgame.input();
	    Cgame.draw();
		
	}
 
	gfxExit();
	
	return 0;
}