#include <iostream>
#include "Globals.h"
#include "config.h"
#include "Engine.h"
#include "TestBench.h"

using namespace main_params;

void RunSuperheatTest();
void RunPowerTest();

int main()
{
	std::cout << "Please, enter ambient temperature: ";
	std::cin >> Temperature::ambient_temperature;

	RunSuperheatTest();
	RunPowerTest();
}


void RunSuperheatTest()
{
	InternalCombustionEngine engine(inertia, moment_to_velocity_dep, superheat_temperature, heat_to_moment_coeff, heat_to_velocity_coeff, cooling_coeff);

	SuperheatTestBench superheat_test_bench;
	superheat_test_bench.AttachEngine(engine);

	switch (superheat_test_bench.RunTest())
	{
	case SuperheatTestBench::ReturnCodes::Success:
		std::cout << "Time to overheat = " << superheat_test_bench.GetTestTime() << " seconds\n";
		break;
	case SuperheatTestBench::ReturnCodes::NonOverheat:
		std::cout << "Engine does not overheat. Max temperature = " << superheat_test_bench.GetEngineMaxTemperature() << std::endl;
		break;
	default:
		std::cout << "Unknown return code" << std::endl;
		break;
	}
}

void RunPowerTest()
{
	InternalCombustionEngine engine(inertia, moment_to_velocity_dep, superheat_temperature, heat_to_moment_coeff, heat_to_velocity_coeff, cooling_coeff);

	PowerTestBench power_test_bench;
	power_test_bench.AttachEngine(engine);

	switch (power_test_bench.RunTest())
	{
	case PowerTestBench::ReturnCodes::Success:
		std::cout << "Max power = " << power_test_bench.GetMaxPower() << " kWatt\n";
		std::cout << "Velocity at max power = " << power_test_bench.GetVelocityAtMaxPower() << " rad/sec\n";
		break;
	default:
		std::cout << "Unknown return code" << std::endl;
		break;
	}
}

