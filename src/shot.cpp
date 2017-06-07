#include "shot.h"
#include <math.h>



Shot::Shot(const int x, const int y, const int rotation) : MovingObject(x, y), mTick(30)
{
	mIdentifier = 3;
	mRotation = rotation;
	mCurrent = new Vector(0, -15);
	mCurrent->rotate(-mRotation);
}
Shot::~Shot()
{
	free();
	delete mCurrent;
	delete mHitbox;
}
void Shot::move(const int screenWidth, const int screenHeight, bool forward)
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
	mTick--;

}

Vector ** Shot::makePolygonVertices(int & numOfVertices)
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

int Shot::getShotTick () const
{
	return mTick;
}
