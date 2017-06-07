#ifndef _GAME_
#define _GAME_ 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "player.h"
#include "asteroid.h"
#include "shot.h"
#include "upgrade.h"
#include "constants.cpp"

using namespace std;

/**
 * Class representing game
 */

class Game
{
public:
	/**
	 * @brief Constructor of object Game
	 * 
	 * @param int reference of highest score loaded from file
	 */
	Game(unsigned int & highScoreInit);
	~Game();
	/**
	 * @brief Method for rendering player
	 * 
	 * @param ren pointer to SDL_Renderer
	 * @param font pointer to font
	 */
	void render(SDL_Renderer * ren, TTF_Font * font) const;
	/**
	 * @brief Method for creating player in game
	 * 
	 * @param surface Image of player
	 * @param ren pointer to SDL_Renderer
	 * @param screenHeight height of screen
	 * @param screenWidth width of screen
	 */
	void makePlayer(SDL_Surface * surface, SDL_Renderer * ren, const int screenHeight, const int screenWidth);
	/**
	 * @brief Method for creating upgrade
	 * 
	 * @param surface Image of player
	 * @param ren pointer to SDL_Renderer
	 * @param centre SDL_Point of place, where upgrade will be spawned
	 */
	void makeUpgrade(SDL_Surface * surface, SDL_Renderer * ren, SDL_Point centre);
	/**
	 * @brief Method for creating asteroids
	 * 
	 * @param surface Image of player
	 * @param ren pointer to SDL_Renderer
	 * @param fin reference on input file stream, where information about spawnpoints of asteroids are stored
	 */
	void makeAsteroids (SDL_Surface ** textureSurfaces, SDL_Renderer * ren, ifstream & fin);
	/**
	 * @brief Method for changing direction of player
	 * 
	 * @param add number of degrees to add
	 */
	void changePlayerAngle (const int add);
	/**
	 * @brief Method for player to shoot
	 * 
	 * @param ren pointer to SDL_Renderer
	 * @param shotSurface image of shot
	 */
	void playerShoot(SDL_Renderer * ren, SDL_Surface * shotSurface);
	/**
	 * @brief Method for moving objects on game window
	 * 
	 * @param forward flag about player pressing forward key
	 * @param screenWidth width of screen
	 * @param screenHeight height of screen
	 */
	void moveObjects (bool forward, const int screenWidth, const int screenHeight);
	/**
	 * @brief Method for checking of collisions between objects
	 * 
	 * @param textureSurfaces array of surfaces for creating textures of asteroids
	 * @param ren pointer of SDL_Renderer
	 * 
	 * @return -1 if player crashed into asteroid
	 * 			1 if player destroyed all asteroids
	 * 			0 if there are asteroids left	
	 */
	int checkCollision(SDL_Surface ** textureSurfaces, SDL_Renderer * ren);
	/**
	 * @brief Method for printing scoreboard
	 * 
	 * @param ren pointer to SDL_Renderer
	 * @param font pointer to font
	 */
	void printScoreBoards(SDL_Renderer * ren, TTF_Font * font) const;
	/**
	 * @brief Method for checking, if hitboxes collides
	 * @remark This methoda is taken from  http://www.phailed.me/2011/02/polygonal-collision-detection/#tut7 
	 * 
	 * @param a hitbox of first object
	 * @param b hitbox of second object
	 * 
	 * @return true if objects collide, false otherwise
	 */
	bool sat (Polygon * a, Polygon * b);
	/**
	 * @brief Method for projection of hitbox on vector
	 * @remark This methoda is taken from  http://www.phailed.me/2011/02/polygonal-collision-detection/#tut7 
	 * 
	 * @param a hitbox of object to project
	 * @param axis axis where hitbox is going to project
	 * 
	 * @return array of min and max values on axis axis
	 */
	double * project(Polygon * a, Vector *axis);
	/**
	 * @brief Method to decide if number n is in interval <low, high>, where low is min(range[0], range[1]) and high is max(range[0], range[1])
	 * @remark This methoda is taken from  http://www.phailed.me/2011/02/polygonal-collision-detection/#tut7 
	 * 
	 * @param n number to test
	 * @param range range where n has to be
	 * 
	 * @return true if range contains n, false otherwise
	 */
	bool contains(double n, double* range);
	/**
	 * @brief Method to decide, if objects overlap on axis
	 * @remark This methoda is taken from  http://www.phailed.me/2011/02/	polygonal-collision-detection/#tut7 
	 * 
	 * @param a_ array of min and max values of object a
	 * @param b_ array of min and max values of object b
	 * 
	 * @return false if objects dont overlap, true otherwise
	 */
	bool overlap(double* a_, double* b_);
protected:
	Player * pl; /*!< pointer to object player */
	int numOfShots; /*!< number of existing shots*/
	int maxShots; /*!< maximum possible shots*/
	MovingObject ** objects; /*!< array of all moving objects*/
	Upgrade * upgrades[MAX_UPGRADES]; /*!< array of all upgrades*/
	unsigned int upgradeDuration [3]; /*!< array of ingame times, when upgrades stops to work*/
	int numOfUpgrades; /*!< number of existing upgrades*/
	int numOfObjects; /*!< number of existing moving objects */
	int maxObjects; /*!< maximum number of possible moving objects */
	unsigned int score; /*!< actual score */
	unsigned int & highScore; /*!< highest score */
};
#endif