#ifndef __Vector__
#define __Vector__ 
#include <math.h>
#include <cstdio>

/**
 * class representing vector
 */

class Vector
{
public:
	/**
	 * @brief Constructor of object vector
	 * 
	 * @param x value of x component
	 * @param y value of y component
	 */
	Vector(const double x, const double y);
	~Vector();
	/**
	 * @brief operator = for object vector
	 * 
	 * @param src object to copy
	 */
	Vector & operator = ( const Vector & src );
	/**
	 * @brief Method to rotate vector
	 * 
	 * @param degree number of degrees to rotate vector
	 */
	void rotate(const double degree);
	/**
	 * @brief Method to print vector
	 */
	void printVector () const;
	/**
	 * @brief Method to add vector to this vector
	 * 
	 * @param x vector to add
	 */
	void addVector (const Vector & x);
	/**
	 * @brief Method to multiply vector by scalar
	 * 
	 * @param mult scalar for multiplying by
	 */
	void multiplyVector (const double mult);
	/**
	 * @brief Getter of magnitude of vector
	 * @return Magnitude of vector
	 */	
	double getAbsolute () const;
	/**
	 * @brief Getter of x component of vector
	 * @return x component of vector
	 */
	double getAxisX () const;
	/**
	 * @brief Getter of y component of vector
	 * @return y component of vector
	 */
	double getAxisY () const;
	/**
	 * @brief Getter of scalar product of two vectors
	 * 
	 * @param x vector to use for product
	 * @return scalar vector of x and this vector
	 */
	double dotProduct(const Vector & x) const;
	/**
	 * @brief Method which creates normalized vector from this vector
	 * @return Normalized vector
	 */
	Vector * normalize () const;
private:
	double axisX; /*!< double value for axisY */
	double axisY; /*!< double value for axisX */
	
};
#endif	