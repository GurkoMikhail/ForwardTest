#pragma once

#include "vector"
#include "algorithm"
#include "assert.h"

class Point
{
public:
	friend class InterpolatedDependency;

	/*-----------------CONSTRUCTORS---------------------*/
	Point(float x, float y);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	~Point();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------GETTERS------------------------*/
	const float& GetX() const;
	const float& GetY() const;
	/*-------------------GETTERS------------------------*/

private:
	float x;
	float y;
};

class InterpolatedDependency : public std::vector<Point>
{
public:
	/*-----------------CONSTRUCTORS---------------------*/
	InterpolatedDependency();
	InterpolatedDependency(const std::vector<float>& x_vec, const std::vector<float>& y_vec);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	~InterpolatedDependency();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------GETTERS------------------------*/
	Point GetInterpolatedPoint(float x) const;
	/*-------------------GETTERS------------------------*/

	/*-------------------PUSHERS------------------------*/
	void PushPoint(Point point);
	void PushPoint(float x, float y);
	/*-------------------PUSHERS------------------------*/

private:
	/*-----------------CALCULATIONS---------------------*/
	void Sort();
	Point Interpolate(float value) const;
	/*-----------------CALCULATIONS---------------------*/

};

