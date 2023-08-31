#include "other.h"

float LinearInterpolation(const std::vector<float>& x_vec, const std::vector<float>& y_vec, float value)
{
	for (unsigned int i = 0; i < x_vec.size() - 1; i++)
	{
		if (value >= x_vec[i + 1] - 1e-6)
			continue;
		return y_vec[i] + ((y_vec[i + 1] - y_vec[i]) / (x_vec[i + 1] - x_vec[i])) * (value - x_vec[i]);
	}
	return y_vec.back();
}