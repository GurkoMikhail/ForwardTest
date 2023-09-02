#include "Interpolation.h"


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
	std::sort(this->begin(), this->end(), [](Point a, Point b) { return a.GetX() < b.GetX(); });
}

Point InterpolatedDependency::Interpolate(float x_value) const
{
	auto& self = *this;

	/*Check boundaries*/
	if (x_value <= self.front().GetX()) { return Point(x_value, self.front().GetY()); }
	if (x_value >= self.back().GetX()) { return Point(x_value, self.back().GetY()); }
	/*--------------------------------------------------------------------------------*/

	/*Find upper bound*/
	auto predicate = [&x_value](const Point& point) { return x_value < point.GetX(); };
	auto upper_bound = std::find_if(self.begin() + 1, self.end(), predicate);
	/*--------------------------------------------------------------------------------*/

	/*Def boundary points*/
	auto& point = upper_bound[-1];
	auto& next_point = upper_bound[0];

	assert(x_value >= point.GetX());
	assert(x_value < next_point.GetX());
	/*--------------------------------------------------------------------------------*/

	/*Interpolating*/
	Point diff_point((next_point.GetX() - point.GetX()), (next_point.GetY() - point.GetY()));
	float y_value = point.GetY() + (diff_point.GetY() / diff_point.GetX()) * (x_value - point.GetX());

	assert(y_value + FLT_EPSILON > std::min(point.GetY(), next_point.GetY()));
	assert(y_value - FLT_EPSILON < std::max(point.GetY(), next_point.GetY()));
	/*--------------------------------------------------------------------------------*/

	return Point(x_value, y_value);
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point::~Point() {}

float Point::GetX() const { return x; }

float Point::GetY() const { return y; }

