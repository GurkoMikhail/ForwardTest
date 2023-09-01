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

void Engine::SetSuperheatTemperature(float superheat_temperature)
{
	this->superheat_temperature = superheat_temperature;
}

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
	const InterpolatedDependency& moment_to_velocity_dep,
	float superheat_temperature,
	float heat_to_moment_coeff,
	float heat_to_velocity_coeff,
	float cooling_coeff
)
{
	SetInertia(inertia);
	SetMomentToVelocityDependency(moment_to_velocity_dep);
	SetSuperheatTemperature(superheat_temperature);
	SetHeatToMomentCoeff(heat_to_moment_coeff);
	SetHeatToVelocityCoeff(heat_to_velocity_coeff);
	SetCoolingCoeff(cooling_coeff);
}

InternalCombustionEngine::~InternalCombustionEngine() {}

void InternalCombustionEngine::SetInertia(float inertia)
{
	this->inertia = inertia;
}

void InternalCombustionEngine::SetMomentToVelocityDependency(const InterpolatedDependency& moment_to_velocity_dep)
{
	this->moment_to_velocity_dep = moment_to_velocity_dep;
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

float InternalCombustionEngine::GetInertia() const { return inertia; }

float InternalCombustionEngine::GetHeatToMomentCoeff() const { return heat_to_moment_coeff; }

float InternalCombustionEngine::GetHeatToVelocityCoeff() const { return heat_to_velocity_coeff; }

float InternalCombustionEngine::GetCoolingCoeff() const { return cooling_coeff; }

void InternalCombustionEngine::SetNextState()
{
	current_velocity += current_acceleration * Time::delta_time;
	current_temperature += current_moment * heat_to_moment_coeff * Time::delta_time;
	current_temperature += (current_velocity * current_velocity) * heat_to_velocity_coeff * Time::delta_time;
	current_temperature += cooling_coeff * (Temperature::ambient_temperature - current_temperature) * Time::delta_time;
	UpdateState();
}

void InternalCombustionEngine::SetStartState()
{
	current_temperature = Temperature::ambient_temperature;
	current_velocity = moment_to_velocity_dep[0].GetX();
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
	Point point = moment_to_velocity_dep.GetInterpolatedPoint(current_velocity);
	return point.GetY();
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

