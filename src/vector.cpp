#include "vector.h"

Vector::Vector(const double x, const double y) : axisX(x), axisY(y)
{
}

Vector::~Vector() 
{
}

Vector & Vector::operator = ( const Vector & src )
{
	if(&src == this)
		return *this;
	axisX = src.axisX;
	axisY = src.axisY;
	return *this;
}

void Vector::rotate(const double degree)
{
	double axX = axisX;
	double axY = axisY;
	double rad = degree * (M_PI / 180);

	axisX = axX * cos(rad) + axY * sin(rad);
	axisY = axY * cos(rad) - axX * sin(rad);
}

void Vector::printVector () const
{
	printf("X: %f, Y: %f\n", axisX, axisY);
}

void Vector::addVector (const Vector & x)
{
	axisX += x.axisX;
	axisY -= x.axisY;
}

void Vector::multiplyVector (const double mult)
{
	axisX *= mult;
	axisY *= mult;
}

double Vector::getAbsolute () const 
{
	return sqrt(fabs(axisX * axisX) + fabs(axisY * axisY));
}

double Vector::getAxisX () const
{
	return axisX;
}

double Vector::getAxisY () const
{
	return axisY;
}

double Vector::dotProduct(const Vector & x) const
{
	return axisX * x.getAxisX() + axisY * x.getAxisY();
}

Vector * Vector::normalize ()const
{
	double magnitude = sqrt(axisX * axisX + axisY * axisY);
	Vector * normalized = new Vector (axisX / magnitude, axisY / magnitude);
	return normalized;
}