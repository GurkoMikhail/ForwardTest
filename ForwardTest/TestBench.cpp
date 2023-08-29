#include "TestBench.h"

/*-----------------------------TestBench----------------------------*/
TestBench::TestBench() {}

TestBench::TestBench(Engine& engine)
{
	AttachEngine(engine);
}

TestBench::~TestBench() {}

void TestBench::AttachEngine(Engine& engine)
{
	this->ptr_engine = &engine;
}

const Engine* TestBench::GetAttachedEnginePtr() const
{
	return ptr_engine;
}

float TestBench::GetTestTime() const
{
	return test_time;
}

bool TestBench::CheckAttachedEngine() const
{
	return ptr_engine != nullptr;
}

int TestBench::RunTest()
{
	if (!CheckAttachedEngine()) { return ReturnCodes::NonAttachedEngine; }

	Engine& engine = *ptr_engine;

	test_time = 0.0f;
	int return_code = ReturnCodes::Failure;
	engine.Start();
	while (engine.GetRunStatus())
	{
		return_code = MakeStep();
		if (return_code != ReturnCodes::Success) { engine.Stop(); }
		test_time += Time::delta_time;
	}
	return return_code;
}
/*-----------------------------TestBench----------------------------*/


/*-------------------------SuperheatTestBench-----------------------*/
SuperheatTestBench::SuperheatTestBench() {}

SuperheatTestBench::SuperheatTestBench(Engine& engine) :TestBench(engine) {}

SuperheatTestBench::~SuperheatTestBench() {}

float SuperheatTestBench::GetEngineMaxTemperature() const { return engine_max_temperature; }

bool SuperheatTestBench::CheckOverheat() const
{
	Engine& engine = *ptr_engine;
	return engine.GetSuperheatTemperature() <= engine.GetCurrentTemperature();
}

bool SuperheatTestBench::CheckReachableOfOverheat() const
{
	Engine& engine = *ptr_engine;
	float delta_temperature = abs(engine.GetCurrentTemperature() - engine_max_temperature);
	return delta_temperature > Accuracy::max_delta_temperature;
}

void SuperheatTestBench::UpdateMaxTemperature()
{
	Engine& engine = *ptr_engine;
	engine_max_temperature = std::max(engine.GetCurrentTemperature(), engine_max_temperature);
}

int SuperheatTestBench::MakeStep()
{
	Engine& engine = *ptr_engine;

	engine.SetNextState();
	if (!CheckReachableOfOverheat())
	{
		engine.Stop();
		test_time = INFINITY;
		return ReturnCodes::NonOverheat;
	}
	UpdateMaxTemperature();
	if (CheckOverheat()) { engine.Stop(); }
	return ReturnCodes::Success;
}
/*-------------------------SuperheatTestBench-----------------------*/


/*---------------------------PowerTestBench-------------------------*/
PowerTestBench::PowerTestBench() {}

PowerTestBench::PowerTestBench(Engine& engine) :TestBench(engine) {}

PowerTestBench::~PowerTestBench() {}

float PowerTestBench::GetMaxPower() const
{
	return engine_max_power;
}
float PowerTestBench::GetVelocityAtMaxPower() const
{
	return engine_velocity_at_max_power;
}

bool PowerTestBench::CheckOverVelocity() const
{
	Engine& engine = *ptr_engine;
	float delta_velocity = abs(engine.GetCurrentVelocity() - engine_max_velocity);
	return delta_velocity < Accuracy::max_delta_velocity;
}

void PowerTestBench::UpdateMaxPower()
{
	Engine& engine = *ptr_engine;

	float engine_current_velocity = engine.GetCurrentVelocity();
	float engine_current_power = engine.GetCurrentPower();

	if (engine_current_power > engine_max_power)
	{
		engine_max_power = engine_current_power;
		engine_velocity_at_max_power = engine_current_velocity;
	}
}

void PowerTestBench::UpdateMaxVelocity()
{
	Engine& engine = *ptr_engine;
	engine_max_velocity = engine.GetCurrentVelocity();
}

int PowerTestBench::MakeStep()
{
	Engine& engine = *ptr_engine;

	engine.SetNextState();
	if (CheckOverVelocity())
	{
		UpdateMaxVelocity();
		engine.Stop();
	}
	UpdateMaxPower();
	UpdateMaxVelocity();
	return ReturnCodes::Success;
}
/*---------------------------PowerTestBench-------------------------*/

