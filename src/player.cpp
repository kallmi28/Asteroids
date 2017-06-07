#include <SDL2/SDL_image.h>
#include "player.h"

Player::Player(const int x, const int y) : MovingObject(x, y), mMaxSpeed(10.0), mXResidue(0.0), mYResidue(0.0),  mSlowTick(0)
{
	mIdentifier = 1;
	mCurrent = new Vector(0,0);
}

Player::~Player()
{
	free();
	delete mCurrent;
	delete mHitbox;
}

void Player::move(const int screenWidth, const int screenHeight, bool forward)
{

	if(forward)
	{	
		Vector tmp (0.0, 0.5);
		tmp.rotate(mRotation);
		mCurrent->addVector(tmp);
		//printf("Rocket Speed: %f\n", mCurrent->getAbsolute());
		if(mCurrent->getAbsolute() > mMaxSpeed + 0.2){
			mCurrent->multiplyVector(0.95);
		}
	}
	else
	{
		if(mSlowTick-- == 0 && fabs(mCurrent->getAxisX()) < 1e4 && fabs(mCurrent->getAxisY()) < 1e4)
		{
			mSlowTick = 5;
			mCurrent->multiplyVector(0.92);
		}
	}
	int addToX = (int) (mCurrent->getAxisX());
	int addToY = (int) (mCurrent->getAxisY());

	mXResidue += mCurrent->getAxisX() - (int) (mCurrent->getAxisX());
	mYResidue += mCurrent->getAxisY() - (int) (mCurrent->getAxisY());

	if(mXResidue >= 1 || mXResidue <= -1)
	{
		addToX += (int) mXResidue;
		mXResidue -= (int) mXResidue;
	}

	if(mYResidue >= 1 || mYResidue <= -1)
	{
		addToY += (int) mYResidue;
		mYResidue -= (int) mYResidue;
	}

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
}

void Player::changeAngle(const int change)
{
	mRotation = (mRotation - change) % 360;
	mHitbox->rotate(change);
}

Vector ** Player::makePolygonVertices(int & numOfVertices)
{
	numOfVertices = 3;
	Vector ** vertices = new Vector* [3];
	vertices[0] = new Vector (- 15,+ 15);
	vertices[1] = new Vector (0, - 15);
	vertices[2] = new Vector (+ 15, + 15);

	return vertices;
}

Shot * Player::shoot (SDL_Surface * loadedSurface, SDL_Renderer * ren)
{
	Shot * shot;
	SDL_Point tmp = mHitbox->getCentre();
	Vector * v = new Vector(0, -15);
	v->rotate(-mRotation);
	shot = new Shot(tmp.x + v->getAxisX(), tmp.y + v->getAxisY(), mRotation);
	delete v;
	shot->loadTexture(loadedSurface, ren);
	return shot;
}
