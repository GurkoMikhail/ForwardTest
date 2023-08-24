#include "TestBench.h"

/*-----------------------------TestBench----------------------------*/
float TestBench::GetTestTime()
{
	return test_time;
}

int TestBench::RunTest(Engine& engine)
{
	int result = ReturnCodes::Failure;
	is_run = true;
	test_time = 0.0f;
	engine.Start();
	while (is_run)
	{
		result = MakeStep(engine);
		if (result != ReturnCodes::Success)
		{
			break;
		}
		test_time += Time::delta_time;
	}
	engine.Stop();
	return result;
}
/*-----------------------------TestBench----------------------------*/


/*-------------------------SuperheatTestBench-----------------------*/
float SuperheatTestBench::GetEngineMaxTemperature() { return engine_max_temperature; }

int SuperheatTestBench::MakeStep(Engine & engine)
{
	if (engine.GetSuperheatTemperature() <= engine.GetCurrentTemperature())
	{
		is_run = false;
	}

	if (abs(engine.GetCurrentTemperature() - engine_max_temperature) < Accuracy::max_delta_temperature)
	{
		is_run = false;
		test_time = INFINITY;
		return ReturnCodes::NonOverheat;
	}

	engine_max_temperature = std::max(engine.GetCurrentTemperature(), engine_max_temperature);
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

int PowerTestBench::MakeStep(Engine & engine)
{
	float engine_current_velocity = engine.GetCurrentVelocity();
	float engine_current_power = engine.GetCurrentPower();
	if (engine_current_power > engine_max_power)
	{
		engine_max_power = engine_current_power;
		engine_velocity_at_max_power = engine_current_velocity;
	}
	if (abs(engine_current_velocity - engine_max_velocity) < Accuracy::max_delta_velocity)
	{
		is_run = false;
	}
	engine_max_velocity = engine_current_velocity;
	return engine.SetNextState();
}
/*---------------------------PowerTestBench-------------------------*/