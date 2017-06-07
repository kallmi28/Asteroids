#include "window.h"

Window::Window() :  ren (NULL), win(NULL), screenWidth(0), screenHeight(0), game(NULL), state(START), nextState(START), font(NULL), buttonPushed(false), highestScore(0)
{
	ifstream tmp;
	tmp.open(HIGH_SCORE_INIT, ios_base::binary);
	tmp.read((char*)&highestScore, sizeof(unsigned int));
	tmp.close();
}

Window::~Window()
{
	for (int i = 0; i < NUM_OF_TEXTURES; ++i)
	{
		SDL_FreeSurface(textureSurfaces[i]);
		textureSurfaces[i] = NULL;
	}
	close();
	ofstream tmp;
	tmp.open(HIGH_SCORE_INIT, ios_base::binary);
	tmp.write((char*)&highestScore, sizeof(unsigned int));
	tmp.close();
}

void Window::close()
{
	TTF_CloseFont( font );
	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );

	font = NULL;
	win = NULL;
	ren = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Window::init (const int width, const int height)
{
	bool success = true;
	screenWidth = width;
	screenHeight = height;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return !success;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		//Create window
		win = SDL_CreateWindow( "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( win == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			return !success;
		}
		else
		{
			//Create renderer for window
			ren = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED  );
			if( ren == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				return !success;
			}
			if( TTF_Init() == -1 )
			{
				printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				return !success;
			}
			font = TTF_OpenFont( "src/config/FreeMono.ttf", 28 );
			if( font == NULL )
			{
				printf( "Failed to font! SDL_ttf Error: %s\n", TTF_GetError() );
				return !success;
			}           
		}
	}
	SDL_SetRenderDrawColor( ren, 0x00, 0x00, 0x00, 0xFF );  
	SDL_RenderClear(ren);
	loadTextures();

	select.w = screenWidth / 2;
	select.h = screenHeight / 10;
	select.x = screenWidth / 4;
	select.y = 2 * (screenHeight / 5);

	return success;
}

void Window::render() const
{
	SDL_SetRenderDrawColor( ren, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( ren );
	printMenu();
	SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawRect(ren, &select);
	SDL_RenderPresent( ren );
}

void Window::loadTextures ()
{
	for (int i = 0; i < NUM_OF_TEXTURES; ++i)
	{
		textureSurfaces[i] = IMG_Load(TEXTURE_IMAGES[i].c_str());
	}
}

void Window::printMenu () const
{
	SDL_Color textColor = { 0xFF, 0xFF , 0xFF, 0xFF };
	SDL_Surface * start = TTF_RenderText_Solid( font, "Start", textColor);
	SDL_Texture * tex = SDL_CreateTextureFromSurface( ren, start );
	SDL_Rect renderQuad = {(screenWidth / 2) - (start->w  / 2), 2 *(screenHeight / 5) + (select.h / 4), start->w, start->h };
	SDL_RenderCopyEx(ren, tex, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	SDL_FreeSurface( start );
	SDL_DestroyTexture( tex );

	start = TTF_RenderText_Solid( font, "Exit", textColor);
	tex = SDL_CreateTextureFromSurface( ren, start );
	renderQuad = { (screenWidth / 2) - (start->w  / 2) , 3 *(screenHeight / 5) + (select.h / 4), start->w, start->h };
	SDL_RenderCopyEx(ren, tex, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	SDL_FreeSurface( start );
	SDL_DestroyTexture( tex );
}

bool Window::changeMenu()
{
	const Uint8 * keyboardState = SDL_GetKeyboardState(NULL);
	state = nextState;
	if(!buttonPushed)
		switch(state)
		{
			case START:
				select.y = 2 * (screenHeight / 5);
				if(keyboardState[SDL_SCANCODE_W])
				{
					nextState = EXIT;
					buttonPushed = true;
				}
				else if(keyboardState[SDL_SCANCODE_S])
				{
					nextState = EXIT;
					buttonPushed = true;
				}
				else if(keyboardState[SDL_SCANCODE_RETURN])
				{
					nextState = GAME;
					buttonPushed = true;
				}
			break;
			case EXIT:
				select.y = 3 * (screenHeight / 5);
				if(keyboardState[SDL_SCANCODE_RETURN])
				{
					buttonPushed = true;
					return true;
				}
				else if(keyboardState[SDL_SCANCODE_W])
				{
					nextState = START;
					buttonPushed = true;
				}
				else if(keyboardState[SDL_SCANCODE_S])
				{
					nextState = START;
					buttonPushed = true;
				}
			break;
			case GAME:
				if(!playGame())
					return true;
				nextState = START;
			break;
		}
	else if(!keyboardState[SDL_SCANCODE_W] 
		 && !keyboardState[SDL_SCANCODE_S] 
		 && !keyboardState[SDL_SCANCODE_RETURN])
		buttonPushed = false;
	return false;
}

bool Window::playGame ()
{
	srand(time(NULL));

	game = new Game(highestScore);
	SDL_Event e;

	bool quit = false;
	bool forward = false;

	unsigned int startTime;
	unsigned int shotTime = 0;
	int level = 0;

	game->makePlayer(textureSurfaces[0], ren, screenHeight, screenWidth);


	ifstream asteroidsData;
	asteroidsData.open(ASTEROIDS_INIT, ios_base::binary);

	startTime = SDL_GetTicks();  

	const Uint8 * keyboardState = SDL_GetKeyboardState(NULL);
	for (level = 0; level < LEVELS; ++level)
	{
		game->makeAsteroids(textureSurfaces, ren, asteroidsData);
		while( !quit )
		{
			unsigned int frameTime = SDL_GetTicks();

			while( SDL_PollEvent( &e ) != 0 )
				if( e.type == SDL_QUIT )
					return false;
			
			if(keyboardState[SDL_SCANCODE_A])
				game->changePlayerAngle(10);
			if (keyboardState[SDL_SCANCODE_D])
				game->changePlayerAngle(-10);

			if(keyboardState[SDL_SCANCODE_RSHIFT])
			{
				if(!shotTime)
					game->playerShoot(ren, textureSurfaces[1]);
				shotTime++;
				shotTime %= 4;
			}
			else
				shotTime = 0;

			if(keyboardState[SDL_SCANCODE_W])
				forward = true;
			else
				forward = false;

			game->moveObjects(forward, screenWidth, screenHeight);
			game->render(ren, font);

			int retVal;
			if((retVal = game->checkCollision(textureSurfaces, ren)))
			{
				if(retVal == 1)
					break;
				else
					goto dead;
			}
			while(SDL_GetTicks() - frameTime < SCREEN_TICK_PER_FRAME);
				//printf("%u - %u > %u\n", SDL_GetTicks(), frameTime, SCREEN_TICK_PER_FRAME);
		}
	}

dead:
	bool buttonPushed = false; 
	unsigned int endTime = SDL_GetTicks();
	while(keyboardState[SDL_SCANCODE_RETURN] || !buttonPushed)
	{
		while( SDL_PollEvent( &e ) != 0 )
			if( e.type == SDL_QUIT )
			{
				delete game;
				return false;
			}
		unsigned int frameTime = SDL_GetTicks();
		game->moveObjects(forward, screenWidth, screenHeight);
		game->render(ren, font);
		while(SDL_GetTicks() - frameTime < SCREEN_TICK_PER_FRAME);
		if(keyboardState[SDL_SCANCODE_RETURN]) buttonPushed = true;
	}

	if(level == 15)
		printf("You won, you have cleared all %d levels. \n", LEVELS);
	else
		printf("You have lost, you made it to %d. level\n", level + 1);
	printf("Your time is %.2f seconds.\n", (endTime - startTime) / 1000.);

	delete game;
	return true;
}
