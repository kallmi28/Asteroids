#ifndef __player__
#define __player__ 
#include <SDL2/SDL.h>
#include "vector.h"
#include "polygon.h"
#include "shot.h"
#include "movingobject.h"

using namespace std;

/**
 * class representing player
 */

class Player : public MovingObject
{
public:
	/**
	 * @brief Constructor of object player
	 * 
	 * @param x x axis of object
	 * @param y y axis of object
	 */
	Player(const int x, const int y);
	~Player();
	/**
	 * @brief Method for moving object
	 * 
	 * @param screenWidth width of window
	 * @param screenHeight height of window
	 * @param forward indicator if player is moving forward
	 */
	void move(const int screenWidth, const int screenHeight, bool forward);
	/**
	 * @brief Method to change angle of player
	 * 
	 * @param change number of degrees to change angle
	 */
	void changeAngle (const int change);
	/**
	 * @brief Method for creating vertices of hitbox
	 * 
	 * @param numOfVertices Number of vertices to create
	 * @return array of vertices of hitbox
	 */
	Vector ** makePolygonVertices(int & numOfVertices);
	/**
	 * @brief Method for player to shoot
	 * 
	 * @param loadedSurface SDL_Surface of image of shot
	 * @param ren pointer to SDL_Renderer
	 * 
	 * @return pointer to new shot
	 */
	Shot * shoot (SDL_Surface * loadedSurface, SDL_Renderer * ren);
protected:
	double mMaxSpeed; /*!< double value representing maximum velocity of player */
	double mXResidue; /*!< double value representing residue of x axis from rounding */
	double mYResidue; /*!< double value representing residue of x axis from rounding */
	int mSlowTick; /*!< integer value used for slowing down player if rocket is not accelerating*/
};
#endif