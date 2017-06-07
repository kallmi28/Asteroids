#ifndef _WINDOW_
#define _WINDOW_ 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <iostream>
#include <fstream>

#include "game.h"
#include "constants.cpp"

using namespace std;

/**
 * Class representing window for program
 */ 

class Window
{
public:
	/**
	 * @brief Construct of Window object
	 */
	Window();
	~Window();
	/**
	 * @brief Method which render new frame
	 */
	void render ()const;
	/**
	 * @brief Method to close SDL things
	 */
	void close ();
	/**
	 * @brief Method for initializating window
	 * @details Method, where i create window and renderer for program, open font, load images for textures and clear window
	 * 
	 * @param width window width
	 * @param height window heigth
	 * 
	 * @return returns success of initialization
	 */
	bool init (const int width, const int height);
	/**
	 * @brief Method to load images to textures
	 */
	void loadTextures ();
	/**
	 * @brief Method for printing menu
	 */
	void printMenu ()const;
	/**
	 * @brief Method to change position in menu
	 * @return true if exit is selected, false otherwise
	 */
	bool changeMenu();
	/**
	 * @brief Method to start game
	 * @details In this method, game is created and player can start playing
	 * @return returns false if window is shutdown by player or CTRL + C, true otherwise
	 */
	bool playGame ();
protected:
	SDL_Renderer * ren; /*!< pointer on SDL_Renderer */
	SDL_Window * win; /*!< pointer on SDL_Window */
	int screenWidth; /*!< integer value representing screen width*/
	int screenHeight; /*!< integer value representing screen height*/
	SDL_Surface * textureSurfaces[NUM_OF_TEXTURES]; /*!< array of surfaces from images to create textures */
	Game * game; /*!< pointer on object game created when start in menu is selected */
	MENU_STATE state; /*!< enum for representing present state */
	MENU_STATE nextState; /*!< enum for representing next state */
	TTF_Font * font; /*!< pointer on font */
	bool buttonPushed; /*!< bool value for representing button was pushed and not released */
	unsigned int highestScore; /*!< integer value for highest score */
	SDL_Rect select; /*!< SDL_Rect for indication of selected option */
};
#endif