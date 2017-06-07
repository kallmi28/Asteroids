#ifndef _movingobject_
#define _movingobject_ 
#include <SDL2/SDL.h>
#include "vector.h"
#include "polygon.h"
#include "constants.cpp"

/**
 * Abstract class representing all moving objects in game
 */

class MovingObject
{
public:
	/**
	 * @brief Constructor of object MovingObject
	 * 
	 * @param x x axis of object
	 * @param y y axis of object
	 */
	MovingObject(const int x, const int y);
	/**
	 * @brief Virtual destructor
	 */
	virtual ~MovingObject();
	/**
	 * @brief Method for moving object
	 * 
	 * @param screenWidth width of window
	 * @param screenHeight height of window
	 * @param forward indicator if player is moving forward (using only for player)
	 */
	virtual void move (const int screenWidth, const int screenHeight, bool forward) = 0;
	/**
	 * @brief Method for render object
	 * 
	 * @param ren pointer on SDL_Renderer
	 */
	void render (SDL_Renderer * ren) const;
	/**
	 * @brief Method for loading texture of object
	 * 
	 * @param loadedSurface SDL_Surface of image 
	 * @param ren pointer on SDL_Renderer
	 * 
	 * @return succes of making texture from surface
	 */
	bool loadTexture(SDL_Surface * loadedSurface, SDL_Renderer* ren);
	/**
	 * @brief Method for freeing SDL_Texture
	 * @details Method frees mTexture and set it on NULL. Also set width and height of texture to 0.
	 */
	void free ();
	/**
	 * @brief Method for creating vertices of hitbox
	 * 
	 * @param numOfVertices Number of vertices to create
	 * @return array of vertices of hitbox
	 */
	virtual Vector ** makePolygonVertices(int & numOfVertices) = 0;
	/**
	 * @brief Getter of object's hitbox
	 * @return Hitbox of object
	 */
	Polygon * getHitbox () const;

protected:
	SDL_Texture *  mTexture; /*!< pointer on SDL_Texture of object*/
	int mX; /*!< integer value representing x axis of object*/
	int mY; /*!< integer value representing y axis of object*/
	int mWidth; /*!< integer value representing width of texture in pixels*/
	int mHeight; /*!< integer value representing height of texture in pixels*/
	Polygon * mHitbox; /*!< pointer on object Polygon representing hitbox of object*/
	Vector * mCurrent; /*!< pointer on vector representing speed and direction of object */
	int mRotation; /*!< integer value representing s*/
	char mIdentifier;
};
#endif