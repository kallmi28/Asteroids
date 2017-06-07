#ifndef __asteroid
#define __asteroid 
#include <SDL2/SDL.h>
#include "vector.h"
#include "polygon.h"
#include "movingobject.h"

/**
 * Class representing asteroids in game
 */

class Asteroid : public MovingObject
{
public:
	/**
	 * @brief Constructor of Asteroid class
	 * 
	 * @param x X axis of object
	 * @param y Y axis of object
	 * @param direction Vector of movemenent for object
	 * @param size size of asteroid
	 */
	Asteroid(const int x, const int y, Vector * direction, const int size);

	~Asteroid();

	/**
	 * @brief Method for moving object
	 * 
	 * @param screenWidth width of window
	 * @param screenHeight height of window
	 * @param forward indicator if player is moving forward (not using in this function)
	 */
	void move(const int screenWidth, const int screenHeight, bool forward = false);

	/**
	 * @brief Method for creating vertices of hitbox
	 * 
	 * @param numOfVertices Number of vertices to create
	 * @return array of vertices of hitbox
	 */
	Vector ** makePolygonVertices(int & numOfVertices);

	/**
	 * @brief Method for splitting asteroids
	 * 
	 * @param textures array of surfaces for creating texture for new asteroid
	 * @param ren pointer on SDL renderer ( needed in creating texture from surface)
	 * 
	 * @return array of two new asteroids if size was bigger then 0, NULL otherwise
	 */
	Asteroid ** split (SDL_Surface ** textures, SDL_Renderer * ren);

	/**
	 * @brief Getter of points for destroying asteroid
	 * @return number of points depending on size of asteroid
	 */
	unsigned int getScore() const;
protected:
	int mSpeedRotation;  /*!< integer value representing swivel speed in degrees*/
	int mSize;	 /*!< integer value representing size of asteroid */
};
#endif