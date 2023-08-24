#pragma once
#include "vector"

namespace main_params
{
	float inertia = 10;
	std::vector<float> velocities{ 0.0f, 75.0f, 150.0f, 200.0f, 250.0f, 300.0f };
	std::vector<float> moments{ 20.0f, 75.0f, 100.0f, 105.0f, 75.0f, 0.0f };
	float superheat_temperature = 110.0f;
	float heat_to_moment_coeff = 0.01f;
	float heat_to_velocity_coeff = 0.0001f;
	float cooling_coeff = 0.1f;
}
