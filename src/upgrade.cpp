#include "upgrade.h"

Upgrade::Upgrade(const int x, const int y, const int type) : mTexture(NULL), mX(x), mY(y), mWidth(0), mHeight(0), mHitbox(NULL), mIdentifier(type)
{

}

Upgrade::~Upgrade()
{
	free();
	delete mHitbox;
}
void Upgrade::render (SDL_Renderer * ren) const
{
	SDL_SetRenderDrawColor( ren, 0xFF, 0x00, 0xFF, 0xFF );
	SDL_Rect renderQuad = { mX, mY, mWidth, mHeight };
	SDL_RenderCopyEx(ren, mTexture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);

	//mHitbox->drawPolygon(ren);
}

bool Upgrade::loadTexture(SDL_Surface * loadedSurface, SDL_Renderer* ren)
{
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
	if( newTexture == NULL )
	{
		printf( "Unable to create texture! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		int numOfVertices = 0;
		//Get image dimensions
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		mX -= mWidth / 2;
		mY -= mHeight / 2;
		SDL_Point centre = {mX + (mWidth / 2), mY + (mHeight / 2)};
		Vector ** vertices = makePolygonVertices(numOfVertices);
		mHitbox = new Polygon (numOfVertices, centre, vertices);

	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Upgrade::free ()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

Polygon * Upgrade::getHitbox () const
{
	return mHitbox;
}

Vector ** Upgrade::makePolygonVertices(int & numOfVertices)
{
	int x = mWidth / 2;
	int y = mHeight / 2;
	numOfVertices = 4;
	Vector ** vertices = new Vector* [4];
	vertices[0] = new Vector (-x, -y);
	vertices[1] = new Vector (+x, -y);
	vertices[2] = new Vector (+x, +y);
	vertices[3] = new Vector (-x, +y);

	return vertices;
}

char Upgrade::getIdentifier () const
{
	return mIdentifier;
}
