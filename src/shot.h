#ifndef __SHOT____
#define __SHOT____
#include <SDL2/SDL.h>
#include "vector.h"
#include "polygon.h"
#include "movingobject.h"

/**
 * Class representing shot 
 */

class Shot : public MovingObject
{
public:
	/**
	 * @brief Constructor of object Shot
	 * 
	 * @param x x axis of object
	 * @param y y axis of object
	 * @param rotation rotation of object
	 */
	Shot(const int x, const int y, const int rotation);
	~Shot();
	/**
	 * @brief Method for moving object
	 * 
	 * @param screenWidth width of window
	 * @param screenHeight height of window
	 * @param forward indicator if player is moving forward (using only for player)
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
	 * @brief Getter of time left for shot
	 * @return number of frames until shot dies
	 */
	int getShotTick () const;
private:
	int mTick; /*!< int value representing number of frames left for shot to live */
};
#endif