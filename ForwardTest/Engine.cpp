#include "Engine.h"


/*-----------------------------Engine----------------------------*/
Engine::Engine() {}

Engine::~Engine() {}

bool Engine::GetRunStatus() const { return is_run; }

float Engine::GetSuperheatTemperature() const { return superheat_temperature; }

float Engine::GetCurrentVelocity() const { return current_velocity; }

float Engine::GetCurrentTemperature() const { return current_temperature; }

float Engine::GetCurrentMoment() const { return current_moment; }

float Engine::GetCurrentPower() const { return current_power; }

float Engine::GetCurrentAcceleration() const { return current_acceleration; }

void Engine::Start()
{
	SetStartState();
	is_run = true;
	UpdateState();
}

void Engine::Stop()
{
	is_run = false;
	UpdateState();
}
/*-----------------------------Engine----------------------------*/


/*---------------------InternalCombustionEngine------------------*/
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

InternalCombustionEngine::~InternalCombustionEngine() {}

void InternalCombustionEngine::SetInertia(float inertia)
{
	this->inertia = inertia;
}

void InternalCombustionEngine::SetHeatToMomentCoeff(float heat_to_moment_coeff)
{
	this->heat_to_moment_coeff = heat_to_moment_coeff;
}

void InternalCombustionEngine::SetHeatToVelocityCoeff(float heat_to_velocity_coeff)
{
	this->heat_to_velocity_coeff = heat_to_velocity_coeff;
}

void InternalCombustionEngine::SetCoolingCoeff(float cooling_coeff)
{
	this->cooling_coeff = cooling_coeff;
}

void InternalCombustionEngine::SetNextState()
{
	current_velocity += current_acceleration * Time::delta_time;
	current_temperature += (current_moment * heat_to_moment_coeff + powf(current_velocity, 2.0f) * heat_to_velocity_coeff) * Time::delta_time;
	current_temperature += cooling_coeff * (Temperature::ambient_temperature - current_temperature) * Time::delta_time;
	UpdateState();
}

void InternalCombustionEngine::SetStartState()
{
	current_temperature = Temperature::ambient_temperature;
	current_velocity = velocity_vec[0];
}

void InternalCombustionEngine::UpdateState()
{
	current_moment = CalcCurrentMoment();
	current_power = CalcCurrentPower();
	current_acceleration = CalcCurrentAcceleration();
}

float InternalCombustionEngine::CalcCurrentMoment() const
{
	if (!is_run)
		return 0.0f;
	return LinearInterpolation(velocity_vec, moment_vec, current_velocity);
}

float InternalCombustionEngine::CalcCurrentPower() const
{
	return current_velocity * current_moment / 1000.0f;
}

float InternalCombustionEngine::CalcCurrentAcceleration() const
{
	return current_moment / inertia;
}
/*---------------------InternalCombustionEngine------------------*/

