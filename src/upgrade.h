#ifndef _UPGRADE
#define _UPGRADE 

#include "polygon.h"
#include <SDL2/SDL.h>

/**
 * Class representing ingame upgrades
 */

class Upgrade
{
public:
	/**
	 * @brief Constructor of object Upgrade
	 * 
	 * @param x X axis of upgrade
	 * @param y Y axis of upgrade
	 * @param type type of upgrade
	 */
	Upgrade(const int x, const int y, const int type);
	~Upgrade();
	/**
	 * @brief Method for rendering object
	 * 
	 * @param ren pointer to SDL_Renderer
	 */
	void render (SDL_Renderer * ren) const;
	/**
	 * @brief Method for creating texture for Upgrade
	 * 
	 * @param loadedSurface Image of texture
	 * @param ren pointer for SDL_Renderer
	 * 
	 * @return success in texture creation
	 */
	bool loadTexture(SDL_Surface * loadedSurface, SDL_Renderer* ren);
	/**
	 * @brief Method for freeing SDL things
	 */
	void free ();
	/**
	 * @brief Getter of objects hitbox
	 * @return Hitbox of object
	 */
	Polygon * getHitbox () const;
	/**
	 * @brief Method for creating vertices of hitbox
	 * 
	 * @param numOfVertices number of vertices to create
	 * @return array of vertices of hitbox
	 */
	Vector ** makePolygonVertices(int & numOfVertices);
	/**
	 * @brief Getter of upgrade type
	 * @return upgrade type
	 */
	char getIdentifier () const;
protected:
	SDL_Texture *  mTexture; /*!< pointer on texture */
	int mX; /*!< integer representing x axis of object */
	int mY; /*!<integer representing y axis of object */
	int mWidth; /*!< integer representing width of texture */
	int mHeight; /*!< integer representing height of texture */
	Polygon * mHitbox; /*!< pointer on hitbox of object */
	char mIdentifier; /*!< value representing type of upgrade */
};
#endif