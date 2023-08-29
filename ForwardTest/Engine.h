#pragma once

#include "Globals.h"
#include "vector"
#include "other.h"


class Engine {

public:
	/*-----------------CONSTRUCTORS---------------------*/
	Engine();
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	virtual ~Engine();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------GETTERS------------------------*/
	bool GetRunStatus() const;
	float GetSuperheatTemperature() const;

	float GetCurrentVelocity() const;
	float GetCurrentTemperature() const;
	float GetCurrentMoment() const;
	float GetCurrentPower() const;
	float GetCurrentAcceleration() const;
	/*-------------------GETTERS------------------------*/

	/*-----------------STATE-CONTROL--------------------*/
	virtual void SetNextState() = 0;
	void Start();
	void Stop();
	/*-----------------STATE-CONTROL--------------------*/

protected:
	float superheat_temperature = 110.0f;

	/*-----------------STATE-FIELDS---------------------*/
	bool is_run = false;
	float current_velocity = 0.0f;
	float current_temperature = Temperature::ambient_temperature;
	float current_moment = 0.0f;
	float current_power = 0.0f;
	float current_acceleration = 0.0f;
	/*-----------------STATE-FIELDS---------------------*/

	/*--------------HIDDEN-STATE-CONTROL----------------*/
	virtual void SetStartState() = 0;
	virtual void UpdateState() = 0;
	/*--------------HIDDEN-STATE-CONTROL----------------*/
};

class InternalCombustionEngine : public Engine
{
public:
	/*-----------------CONSTRUCTORS---------------------*/
	InternalCombustionEngine(
		float inertia = 10.0f,
		std::vector<float> velocities = { 0.0f, 75.0f, 150.0f, 200.0f, 250.0f, 300.0f },
		std::vector<float> moments = { 20.0f, 75.0f, 100.0f, 105.0f, 75.0f, 0.0f },
		float superheat_temperature = 110.0f,
		float heat_to_moment_coeff = 0.01f,
		float heat_to_velocity_coeff = 0.0001f,
		float cooling_coeff = 0.1f
	);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	~InternalCombustionEngine() override;
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------SETTERS------------------------*/
	void SetInertia(float inertia);
	void SetHeatToMomentCoeff(float heat_to_moment_coeff);
	void SetHeatToVelocityCoeff(float heat_to_velocity_coeff);
	void SetCoolingCoeff(float cooling_coeff);
	/*-------------------SETTERS------------------------*/

	/*-----------------STATE-CONTROL--------------------*/
	void SetNextState() override;
	/*-----------------STATE-CONTROL--------------------*/

protected:
	float inertia;
	float heat_to_moment_coeff;
	float heat_to_velocity_coeff;
	float cooling_coeff;
	std::vector<float> velocity_vec;
	std::vector<float> moment_vec;

	/*--------------HIDDEN-STATE-CONTROL----------------*/
	void UpdateState() override;
	void SetStartState() override;
	/*--------------HIDDEN-STATE-CONTROL----------------*/

	/*-------------------CALCULATIONS-------------------*/
	float CalcCurrentMoment() const;
	float CalcCurrentPower() const;
	float CalcCurrentAcceleration() const;
	/*-------------------CALCULATIONS-------------------*/
};

