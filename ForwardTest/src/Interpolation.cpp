#include "Interpolation.h"


InterpolatedDependency::InterpolatedDependency() {}

InterpolatedDependency::InterpolatedDependency(const std::vector<float>& x_vec, const std::vector<float>& y_vec)
{
	auto& container = *this;

	size_t size = std::min(x_vec.size(), y_vec.size());
	container.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		container.push_back(Point(x_vec[i], y_vec[i]));
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
	auto& container = *this;

	container.push_back(point);
	Sort();
}

void InterpolatedDependency::PushPoint(float x, float y)
{
	PushPoint(Point(x, y));
}

void InterpolatedDependency::Sort()
{
	auto& container = *this;

	std::sort(container.begin(), container.end(), [](Point a, Point b) { return a.GetX() < b.GetX(); });
}

Point InterpolatedDependency::Interpolate(float x_value) const
{
	auto& container = *this;

	if (x_value < container.front().GetX()) { return Point(x_value, container.front().GetY()); }
	if (x_value > container.back().GetX()) { return Point(x_value, container.back().GetY()); }

	float y_value = NAN;

	for (int i = 0; i < container.size() - 1; i++)
	{
		const Point& point = container[i];
		const Point& next_point = container[i + 1];

		if (x_value >= next_point.GetX()) { continue; }

		Point diff_point((next_point.GetX() - point.GetX()), (next_point.GetY() - point.GetY()));

		y_value = point.GetY() + (diff_point.GetY() / diff_point.GetX()) * (x_value - point.GetX());

		return Point(x_value, y_value);
	}
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

