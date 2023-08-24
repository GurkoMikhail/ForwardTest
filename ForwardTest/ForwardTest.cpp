#include <iostream>
#include "Globals.h"
#include "config.h"
#include "Engine.h"
#include "TestBench.h"
using namespace main_params;


int RunSuperheatTest()
{
	InternalCombustionEngine engine(inertia, velocities, moments, superheat_temperature, heat_to_moment_coeff, heat_to_velocity_coeff, cooling_coeff);

	SuperheatTestBench superheat_test_bench;
	if (superheat_test_bench.RunTest(engine) == ReturnCodes::NonOverheat)
	{
		std::cout << "Engine does not superheat. Max temperature = " << superheat_test_bench.GetEngineMaxTemperature() << std::endl;
	}
	else
	{
		std::cout << "Time to superheat = " << superheat_test_bench.GetTestTime() << " seconds\n";
		return ReturnCodes::Success;
	}
	return ReturnCodes::Failure;
}


int RunPowerTest()
{
	/*--------------------------PowerTest-------------------------------------*/
	InternalCombustionEngine engine(inertia, velocities, moments, superheat_temperature, heat_to_moment_coeff, heat_to_velocity_coeff, cooling_coeff);

	PowerTestBench power_test_bench;

	if (power_test_bench.RunTest(engine) > 0)
	{
		std::cout << "Power test error\n";
		return ReturnCodes::Failure;
	}
	std::cout << "Max power = " << power_test_bench.GetMaxPower() << " kWatt\n";
	std::cout << "Velocity at max power = " << power_test_bench.GetVelocityAtMaxPower() << " rad/sec\n";
	return ReturnCodes::Success;
	/*--------------------------PowerTest-------------------------------------*/
}


int main()
{
	std::cout << "Please, enter ambient temperature: ";
	std::cin >> Temperature::ambient_temperature;

	RunSuperheatTest();
	RunPowerTest();
}
