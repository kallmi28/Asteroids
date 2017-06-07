 #include "movingobject.h"

MovingObject::MovingObject(const int x, const int y): mTexture(NULL), mX(x), mY(y), mWidth(0), mHeight(0), mHitbox(NULL), mCurrent(NULL), mRotation(0), mIdentifier(0)
{

}

MovingObject::~MovingObject()
{
	
}

void MovingObject::render (SDL_Renderer * ren) const
{
	SDL_Rect renderQuad = { mX, mY, mWidth, mHeight };
	SDL_RenderCopyEx(ren, mTexture, NULL, &renderQuad, mRotation, NULL, SDL_FLIP_NONE);
	switch(mIdentifier)
	{
		case 1:
			SDL_SetRenderDrawColor( ren, 0xFF, 0x00, 0x00, 0xFF );
		break;
		case 2:
			SDL_SetRenderDrawColor( ren, 0x00, 0xFF, 0xFF, 0xFF );
		break;
		case 3:
			SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0x00, 0xFF );
		break;
		default:
			SDL_SetRenderDrawColor( ren, 0x00, 0x00, 0x00, 0xFF );
	}
	if(DEBUG)
		mHitbox->drawPolygon(ren);
}

bool MovingObject::loadTexture(SDL_Surface * loadedSurface, SDL_Renderer* ren)
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

void MovingObject::free ()
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

Polygon * MovingObject::getHitbox () const
{
	return mHitbox;
}
