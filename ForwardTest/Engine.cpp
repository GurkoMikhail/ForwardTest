#include "Engine.h"

/*-----------------------------Engine----------------------------*/
bool Engine::GetRunStatus() { return is_run; }

float Engine::GetCurrentVelocity() { return current_velocity; }

float Engine::GetCurrentTemperature() { return current_temperature; }

float Engine::GetSuperheatTemperature() { return superheat_temperature; }

float Engine::GetCurrentMoment() { return current_moment; }

float Engine::GetCurrentPower() { return current_mower; }

float Engine::GetCurrentAcceleration() { return current_acceleration; }

void Engine::Start()
{
	current_temperature = Temperature::ambient_temperature;
	current_velocity = velocity_vec[0];
	is_run = true;
	Update();
}

void Engine::Stop()
{
	is_run = false;
	Update();
}
/*-----------------------------Engine----------------------------*/


/*---------------InternalCombustionEngineProperties--------------*/
void InternalCombustionEngineProperties::SetInertia(float inertia)
{
	this->inertia = inertia;
}

void InternalCombustionEngineProperties::SetHeatToMomentCoeff(float heat_to_moment_coeff)
{
	this->heat_to_moment_coeff = heat_to_moment_coeff;
}

void InternalCombustionEngineProperties::SetHeatToVelocityCoeff(float heat_to_velocity_coeff)
{
	this->heat_to_velocity_coeff = heat_to_velocity_coeff;
}

void InternalCombustionEngineProperties::SetCoolingCoeff(float cooling_coeff)
{
	this->cooling_coeff = cooling_coeff;
}
/*---------------InternalCombustionEngineProperties--------------*/

/*---------------------InternalCombustionEngine------------------*/
int InternalCombustionEngine::Update()
{
	current_moment = CulcCurrentMoment();
	current_mower = CulcCurrentPower();
	current_acceleration = CulcCurrentAcceleration();
	return ReturnCodes::Success;
}

InternalCombustionEngine::InternalCombustionEngine(
	float inertia,
	std::vector<float> velocities,
	std::vector<float> moments,
	float superheat_temperature,
	float heat_to_moment_coeff,
	float heat_to_velocity_coeff,
	float cooling_coeff
)
{
	this->inertia = inertia;
	velocity_vec = velocities;
	moment_vec = moments;
	this->superheat_temperature = superheat_temperature;
	this->heat_to_moment_coeff = heat_to_moment_coeff;
	this->heat_to_velocity_coeff = heat_to_velocity_coeff;
	this->cooling_coeff = cooling_coeff;
}

int InternalCombustionEngine::SetNextState()
{
	current_velocity += current_acceleration * Time::delta_time;
	current_temperature += (current_moment * heat_to_moment_coeff + powf(current_velocity, 2.0f) * heat_to_velocity_coeff) * Time::delta_time;
	current_temperature += cooling_coeff * (Temperature::ambient_temperature - current_temperature) * Time::delta_time;
	return Update();
}

float InternalCombustionEngine::CulcCurrentMoment()
{
	if (!is_run)
		return 0.0f;
	return LinearInterpolation(velocity_vec, moment_vec, current_velocity);
}

float InternalCombustionEngine::CulcCurrentPower()
{
	return current_velocity * current_moment / 1000.0f;
}

float InternalCombustionEngine::CulcCurrentAcceleration()
{
	return current_moment / inertia;
}

/*---------------------InternalCombustionEngine------------------*/

