#pragma once

#include "Globals.h"
#include "Engine.h"

class TestBench
{
public:
	/*-----------------CONSTRUCTORS---------------------*/
	TestBench();
	TestBench(Engine& engine);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	virtual ~TestBench();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------SETTERS------------------------*/
	void AttachEngine(Engine& engine);
	/*-------------------SETTERS------------------------*/

	/*-------------------GETTERS------------------------*/
	const Engine* GetAttachedEnginePtr() const;
	float GetTestTime() const;
	/*-------------------GETTERS------------------------*/

	/*----------------STATE-CONTROL---------------------*/
	bool CheckAttachedEngine() const;
	int RunTest();
	/*----------------STATE-CONTROL---------------------*/

protected:
	float test_time = 0.0f;
	Engine* ptr_engine = nullptr;

	virtual int MakeStep() = 0;
};

class SuperheatTestBench : public TestBench
{
public:
	/*-----------------CONSTRUCTORS---------------------*/
	SuperheatTestBench();
	SuperheatTestBench(Engine& engine);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	virtual ~SuperheatTestBench();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------GETTERS------------------------*/
	float GetEngineMaxTemperature() const;
	/*-------------------GETTERS------------------------*/

protected:
	/*----------------STATE-CONTROL---------------------*/
	bool CheckOverheat() const;
	bool CheckReachableOfOverheat() const;
	void UpdateMaxTemperature();
	int MakeStep() override;
	/*----------------STATE-CONTROL---------------------*/

	float engine_max_temperature = -FLT_MAX;
};

class PowerTestBench : public TestBench
{
public:
	/*-----------------CONSTRUCTORS---------------------*/
	PowerTestBench();
	PowerTestBench(Engine& engine);
	/*-----------------CONSTRUCTORS---------------------*/

	/*------------------DESTRUCTOR----------------------*/
	virtual ~PowerTestBench();
	/*------------------DESTRUCTOR----------------------*/

	/*-------------------GETTERS------------------------*/
	float GetMaxPower() const;
	float GetVelocityAtMaxPower() const;
	/*-------------------GETTERS------------------------*/

protected:
	/*----------------STATE-CONTROL---------------------*/
	bool CheckOverVelocity() const;
	void UpdateMaxPower();
	void UpdateMaxVelocity();
	int MakeStep() override;
	/*----------------STATE-CONTROL---------------------*/

	float engine_max_power = -FLT_MAX;
	float engine_max_velocity = -FLT_MAX;
	float engine_velocity_at_max_power = -FLT_MAX;
};

