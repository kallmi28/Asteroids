#include "asteroid.h"

Asteroid::Asteroid(const int x, const int y, Vector * direction, const int size) : MovingObject(x,y), mSpeedRotation(0), mSize(size)
{
	mIdentifier = 2;
	mCurrent = direction;
	//mX += mCurrent->getAxisX();
	//mY += mCurrent->getAxisY();

	mRotation = (rand() % 4 )* 90;	
	while(!mSpeedRotation)
		mSpeedRotation = rand() % 11 - 5;
}


Asteroid::~Asteroid()
{
	delete mCurrent;
	delete mHitbox;
}

void Asteroid::move(int screenWidth, int screenHeight, bool forward)
{
	int addToX = mCurrent->getAxisX();
	int addToY = mCurrent->getAxisY();

	mX += addToX;
	mY += addToY;

	mHitbox->movePolygon(addToX, addToY, screenWidth, screenHeight, mHeight / 2);

	if(mX > screenWidth - (mWidth / 2))
		mX = 0;
	else if (mX + (mWidth / 2) < 0 )
		mX = screenWidth - mWidth;

	if(mY > screenHeight - (mHeight / 2))
		mY = 0;
	else if (mY + (mHeight / 2) < 0)
		mY = screenHeight - mHeight;

	mRotation = (mRotation + mSpeedRotation) % 360;
	mHitbox->rotate(-mSpeedRotation);

}

Vector ** Asteroid::makePolygonVertices(int & numOfVertices)
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


Asteroid ** Asteroid::split (SDL_Surface ** textures, SDL_Renderer * ren)
{
	if(mSize == 0) return NULL;
	Vector * as1 = new Vector(*mCurrent);
	Vector * as2 = new Vector(*mCurrent);

	as1->rotate(90);
	as2->rotate(-90);

	Asteroid ** ret = new Asteroid* [2];
	ret[0] = new Asteroid (mX, mY, as1, mSize - 1);
	ret[1] = new Asteroid (mX, mY, as2, mSize - 1);

	ret[0]->loadTexture(textures[2 + (rand() % 2) + ((2 - mSize) + 1) * 2], ren);
	ret[1]->loadTexture(textures[2 + (rand() % 2) + ((2 - mSize) + 1) * 2], ren);


	return ret;
}

unsigned int Asteroid::getScore() const
{
	return 10 * (1 << (2 - mSize));
}
