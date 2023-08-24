#include "TestBench.h"

/*-----------------------------TestBench----------------------------*/
float TestBench::GetTestTime()
{
	return test_time;
}

int TestBench::RunTest(Engine& engine)
{
	int result = ReturnCodes::Failure;
	test_time = 0.0f;
	engine.Start();
	while (engine.GetRunStatus())
	{
		result = MakeStep(engine);
		if (result != ReturnCodes::Success)
		{
			engine.Stop();
		}
		test_time += Time::delta_time;
	}
	return result;
}
/*-----------------------------TestBench----------------------------*/


/*-------------------------SuperheatTestBench-----------------------*/
float SuperheatTestBench::GetEngineMaxTemperature() { return engine_max_temperature; }

bool SuperheatTestBench::CheckOverheat(Engine& engine)
{
	return engine.GetSuperheatTemperature() <= engine.GetCurrentTemperature();
}

bool SuperheatTestBench::CheckReachableOfOverheat(Engine& engine)
{
	return abs(engine.GetCurrentTemperature() - engine_max_temperature) < Accuracy::max_delta_temperature;
}

void SuperheatTestBench::UpdateMaxTemperature(Engine& engine)
{
	engine_max_temperature = std::max(engine.GetCurrentTemperature(), engine_max_temperature);
}

int SuperheatTestBench::MakeStep(Engine& engine)
{
	if (CheckOverheat(engine)) { engine.Stop(); }
	if (CheckReachableOfOverheat(engine))
	{
		engine.Stop();
		test_time = INFINITY;
		return ReturnCodes::NonOverheat;
	}
	UpdateMaxTemperature(engine);
	return engine.SetNextState();
}
/*-------------------------SuperheatTestBench-----------------------*/


/*---------------------------PowerTestBench-------------------------*/

float PowerTestBench::GetMaxPower()
{
	return engine_max_power;
}
float PowerTestBench::GetVelocityAtMaxPower()
{
	return engine_velocity_at_max_power;
}

void PowerTestBench::UpdateMaxPower(Engine& engine)
{
	float engine_current_velocity = engine.GetCurrentVelocity();
	float engine_current_power = engine.GetCurrentPower();

	if (engine_current_power > engine_max_power)
	{
		engine_max_power = engine_current_power;
		engine_velocity_at_max_power = engine_current_velocity;
	}
}

void PowerTestBench::UpdateMaxVelocity(Engine& engine)
{
	engine_max_velocity = engine.GetCurrentVelocity();
}

bool PowerTestBench::CheckOverVelocity(Engine& engine)
{
	return abs(engine.GetCurrentVelocity() - engine_max_velocity) < Accuracy::max_delta_velocity;
}

int PowerTestBench::MakeStep(Engine & engine)
{
	UpdateMaxPower(engine);
	if (CheckOverVelocity(engine))
	{
		engine.Stop();
	}
	UpdateMaxVelocity(engine);
	return engine.SetNextState();
}
/*---------------------------PowerTestBench-------------------------*/