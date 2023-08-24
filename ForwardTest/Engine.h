#pragma once

#include "Globals.h"
#include "vector"
#include "other.h"

class Engine {

protected:
	bool is_run = false;
	std::vector<float> velocity_vec;
	std::vector<float> moment_vec;
	float current_velocity = 0.0f;
	float current_temperature = 0.0f;
	float superheat_temperature = 0.0f;
	float current_moment = 0.0f;
	float current_mower = 0.0f;
	float current_acceleration = 0.0f;

public:
	/*-------------------GETTERS------------------------*/
	bool GetRunStatus();
	float GetCurrentVelocity();
	float GetCurrentTemperature();
	float GetSuperheatTemperature();
	float GetCurrentMoment();
	float GetCurrentPower();
	float GetCurrentAcceleration();
	/*-------------------GETTERS------------------------*/

	/*-------------------CULCULATIONS-------------------*/
	virtual float CulcCurrentMoment() = 0;
	virtual float CulcCurrentPower() = 0;
	virtual float CulcCurrentAcceleration() = 0;
	/*-------------------CULCULATIONS-------------------*/

	/*-----------------STATE-CONTROL--------------------*/
	virtual int Update() = 0;
	virtual int SetNextState() = 0;
	void Start();
	void Stop();
	/*-----------------STATE-CONTROL--------------------*/

};

class InternalCombustionEngineProperties
{
protected:
	float inertia;
	float heat_to_moment_coeff;
	float heat_to_velocity_coeff;
	float cooling_coeff;

public:

	/*-------------------SETTERS------------------------*/
	void SetInertia(float inertia);
	void PushVelocityToMomentPoint(float velocity, float moment);
	void SetHeatToMomentCoeff(float heat_to_moment_coeff);
	void SetHeatToVelocityCoeff(float heat_to_velocity_coeff);
	void SetCoolingCoeff(float cooling_coeff);
	/*-------------------SETTERS------------------------*/
};

class InternalCombustionEngine : public Engine, public InternalCombustionEngineProperties
{
public:
	InternalCombustionEngine(
		float inertia,
		std::vector<float> velocities,
		std::vector<float> moments,
		float superheat_temperature,
		float heat_to_moment_coeff,
		float heat_to_velocity_coeff,
		float cooling_coeff
	);
	int SetNextState();
	float CulcCurrentMoment();
	float CulcCurrentPower();
	float CulcCurrentAcceleration();

protected:
	int Update();

};
float LinearInterpolation(std::vector<float> const& x_vec, std::vector<float> const& y_vec, float value);