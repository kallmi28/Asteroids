#include "polygon.h"

Polygon::Polygon(const int n, SDL_Point centre, Vector ** vertices) : mNumOfVertices(n), mCentre(centre), mVerticesVectors(vertices)
{
	mEdges = new Vector * [n];
	for (int i = 0; i < n; ++i)
	{
		int x1 = centre.x + mVerticesVectors[(i + 1) % n]->getAxisX();
		int y1 = centre.y + mVerticesVectors[(i + 1) % n]->getAxisY();

		int x2 = centre.x + mVerticesVectors[i % n]->getAxisX();
		int y2 = centre.y + mVerticesVectors[i % n]->getAxisY();

		mEdges[i] = new Vector (x1 - x2, y1 - y2);
	}
}

Polygon::~Polygon()
{
	for (int i = 0; i < mNumOfVertices; ++i)
	{
		delete mEdges[i];
		delete mVerticesVectors[i];
	}
	delete[] mEdges;
	delete[] mVerticesVectors;
}
void Polygon::drawPolygon(SDL_Renderer * ren) const
{
	SDL_RenderDrawPoint(ren, mCentre.x, mCentre.y);
	for (int i = 0; i < mNumOfVertices; ++i)
	{
		SDL_RenderDrawLine(ren, 
		mCentre.x + mVerticesVectors[i]->getAxisX(),
		mCentre.y + mVerticesVectors[i]->getAxisY(),
		mCentre.x + mVerticesVectors[(i) % mNumOfVertices]->getAxisX() + mEdges[i]->getAxisX(),
		mCentre.y + mVerticesVectors[(i) % mNumOfVertices]->getAxisY() + mEdges[i]->getAxisY());
		
		SDL_RenderDrawLine(ren,
		mCentre.x,
		mCentre.y,
		mCentre.x + mVerticesVectors[(i + 1) % mNumOfVertices]->getAxisX(),
		mCentre.y + mVerticesVectors[(i + 1) % mNumOfVertices]-> getAxisY());
	}
}

void Polygon::rotate(const int change)
{
	for (int i = 0; i < mNumOfVertices; ++i)
	{
		mEdges[i]->rotate(change);
		mVerticesVectors[i]->rotate(change);
	}
}

void Polygon::movePolygon (const int xChange, const int yChange, const int screenWidth, const int screenHeight, const int halfTexture)
{
	mCentre.x += xChange;
	mCentre.y += yChange;

	if(mCentre.x < 0)
		mCentre.x = screenWidth - halfTexture;
	else if (mCentre.x > screenWidth)
		mCentre.x = halfTexture;
	if(mCentre.y < 0)
		mCentre.y = screenHeight - halfTexture;
	else if (mCentre.y > screenHeight)
		mCentre.y = halfTexture;

}

Vector ** Polygon::getEdges () const
{
	return mEdges;
}

Vector ** Polygon::getVertices () const
{
	return mVerticesVectors;
}

int Polygon::getNumOfVertices () const
{
	return mNumOfVertices;
}

SDL_Point Polygon::getCentre () const
{
	return mCentre;
}

