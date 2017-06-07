#include "window.h"

/** @mainpage Asteroids, BI-PA2
	@author	Miroslav Kallus
	@date	13. 5. 2017
	@version 1
	
	Asteroids is a game where you play as rocket. Your task is to destroy all asteroids in all 15 levels. 

	In menu, you can choose from two options, start, which starts the game, or exit, which close the program. In menu, you can navigate by pressing W key (MENU UP), S key (MENU DOWN) or Return key (select). 

	There is score board located on game window. The upper score shows present score, the bottom score shows highest score. If your present score is now highest, scoreboard changes color to yellow.

	In game you are controlling rocket ship. This rocket ship is able to shoot (Right Shift), move forward (W) and turn left (A) or right (D). After every destroyed asteroid, there is a chance to spawn upgrade, which can temporarily increase number of existing shots at one time or  make your rocket invincible. There is one downgrade, which make your rocket invisible therefore make it harder to avoid asteroids.

	After game ends, game waits until Return key is pushed, after this, you are sent to menu.
*/

int main(int argc, char const *argv[])
{
	Window w;
	w.init(800, 600);
	SDL_Event e;

	bool quit = false;
	bool exit = false;


	while( !quit && !exit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
		exit = w.changeMenu();
		w.render();
	}

	w.close();
	return 0;
}