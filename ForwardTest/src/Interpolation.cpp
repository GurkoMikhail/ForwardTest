#include "Interpolation.h"


/*-----------------------------Point-----------------------------*/
Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point::~Point() {}

const float& Point::GetX() const { return x; }

const float& Point::GetY() const { return y; }
/*-----------------------------Point-----------------------------*/


/*---------------------InterpolatedDependency--------------------*/
InterpolatedDependency::InterpolatedDependency() {}

InterpolatedDependency::InterpolatedDependency(const std::vector<float>& x_vec, const std::vector<float>& y_vec)
{
	size_t size = std::min(x_vec.size(), y_vec.size());
	this->reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		this->push_back(Point(x_vec[i], y_vec[i]));
	}
	Sort();
}

InterpolatedDependency::~InterpolatedDependency() {}

Point InterpolatedDependency::GetInterpolatedPoint(float x) const
{
	return Interpolate(x);
}

void InterpolatedDependency::PushPoint(Point point)
{
	this->push_back(point);
	Sort();
}

void InterpolatedDependency::PushPoint(float x, float y)
{
	PushPoint(Point(x, y));
}

void InterpolatedDependency::Sort()
{
	auto predicate = [](Point a, Point b) { return a.x < b.x; };
	std::sort(this->begin(), this->end(), predicate);
}

Point InterpolatedDependency::Interpolate(float x_value) const
{
	auto& self = *this;

	/*Check boundaries*/
	if (x_value <= self.front().x) { return Point(x_value, self.front().y); }
	if (x_value >= self.back().x) { return Point(x_value, self.back().y); }
	/*--------------------------------------------------------------------------------*/

	/*Find upper bound*/
	auto predicate = [&x_value](const Point& point) { return x_value < point.x; };
	auto upper_bound = std::find_if(self.begin() + 1, self.end(), predicate);
	/*--------------------------------------------------------------------------------*/

	/*Def boundary points*/
	auto& point = upper_bound[-1];
	auto& next_point = upper_bound[0];

	assert(x_value >= point.x);
	assert(x_value < next_point.x);
	/*--------------------------------------------------------------------------------*/

	/*Interpolating*/
	Point diff_point((next_point.x - point.x), (next_point.y - point.y));
	float y_value = point.y + (diff_point.y / diff_point.x) * (x_value - point.x);

	assert(y_value + FLT_EPSILON > std::min(point.y, next_point.y));
	assert(y_value - FLT_EPSILON < std::max(point.y, next_point.y));
	/*--------------------------------------------------------------------------------*/

	return Point(x_value, y_value);
}
/*---------------------InterpolatedDependency--------------------*/

