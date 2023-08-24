#pragma once

#include "Globals.h"
#include "Engine.h"

class TestBench
{
protected:
	bool is_run = false;
	float test_time = 0.0f;

	virtual int MakeStep(Engine& engine) = 0;

public:
	/*-------------------GETTERS------------------------*/
	float GetTestTime();
	/*-------------------GETTERS------------------------*/

	int RunTest(Engine& engine);
};

class SuperheatTestBench : public TestBench
{
public:
	SuperheatTestBench() {};
	float GetEngineMaxTemperature();

protected:
	int MakeStep(Engine& engine);

	float engine_max_temperature = -1.0f;
};

class PowerTestBench : public TestBench
{
public:
	PowerTestBench() {};
	float GetMaxPower();
	float GetVelocityAtMaxPower();

protected:
	int MakeStep(Engine& engine);

	float engine_max_power = -1.0f;
	float engine_max_velocity = -1.0f;
	float engine_velocity_at_max_power = -1.0f;

};
