#ifndef Polygon___
#define Polygon___
#include <SDL2/SDL.h>
#include "vector.h"

/**
 * Class representing Polygon used for Hitboxes
 */

class Polygon
{
public:
	/**
	 * @brief Constructor of object Polygon	
	 * 
	 * @param n number of vertices
	 * @param centre SDL_Point representing centre
	 * @param vertices array of vertices
	 */
	Polygon(const int n, SDL_Point centre, Vector ** vertices);
	~Polygon();
	/**
	 * @brief Method for drawing polygon
	 * 
	 * @param ren pointer on SDL_Renderer
	 */
	void drawPolygon(SDL_Renderer * ren) const;
	/**
	 * @brief Method to rotate polygon
	 * 
	 * @param change change in degrees
	 */
	void rotate (const int change);
	/**
	 * @brief Method for moving object on window
	 * 
	 * @param xChange change on x axis
	 * @param yChange change on y axis
	 * @param screenWidth width of screen
	 * @param screenHeight height of screen
	 * @param halfTexture coords of half of texture
	 */
	void movePolygon (const int xChange, const int yChange, const int screenWidth, const int screenHeight, const int halfTexture);
	/**
	 * @brief Getter of edges 
	 * @return array of edges of polygon
	 */
	Vector ** getEdges () const;
	/**
	 * @brief Getter of vertices 
	 * @return array of vertices of polygon
	 */	
	Vector ** getVertices () const;
	/**
	 * @brief Getter of number of vertices
	 * @return number of vertices
	 */
	int getNumOfVertices () const;
	/**
	 * @brief Getter of centre of polygon
	 * @return SDL_Point representing centre of polygon
	 */
	SDL_Point getCentre () const;
protected:
	int mNumOfVertices; /*!< int value representing number of vertices in polygon */

	SDL_Point mCentre; /*!< SDL_Point representing centre of polygon */
	Vector ** mVerticesVectors; /*!< array of vectors representing vertices */
	Vector ** mEdges; /*!< array of vectors representing edges */
	
};
#endif