#pragma once

#include "Globals.h"
#include "vector"
#include "Interpolation.h"


class Engine {

public:
	/*-----------------CONSTRUCTORS---------------------*/
	Engine();
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	virtual ~Engine();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------SETTERS------------------------*/
	void SetSuperheatTemperature(float superheat_temperature);
	/*-------------------SETTERS------------------------*/

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
	float superheat_temperature = NAN;

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
		float inertia,
		const InterpolatedDependency& moment_to_velocity_dep,
		float superheat_temperature,
		float heat_to_moment_coeff,
		float heat_to_velocity_coeff,
		float cooling_coeff
	);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	~InternalCombustionEngine() override;
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------SETTERS------------------------*/
	void SetInertia(float inertia);
	void SetMomentToVelocityDependency(const InterpolatedDependency& moment_to_velocity_dep);
	void SetHeatToMomentCoeff(float heat_to_moment_coeff);
	void SetHeatToVelocityCoeff(float heat_to_velocity_coeff);
	void SetCoolingCoeff(float cooling_coeff);
	/*-------------------SETTERS------------------------*/

	/*-------------------GETTERS------------------------*/
	float GetInertia() const;
	float GetHeatToMomentCoeff() const;
	float GetHeatToVelocityCoeff() const;
	float GetCoolingCoeff() const;
	/*-------------------GETTERS------------------------*/

	/*-----------------STATE-CONTROL--------------------*/
	void SetNextState() override;
	/*-----------------STATE-CONTROL--------------------*/

protected:
	float inertia;
	InterpolatedDependency moment_to_velocity_dep;
	float heat_to_moment_coeff;
	float heat_to_velocity_coeff;
	float cooling_coeff;

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

