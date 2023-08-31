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
	Engine* GetAttachedEnginePtr() const;
	float GetTestTime() const;
	/*-------------------GETTERS------------------------*/

	/*----------------STATE-CONTROL---------------------*/
	enum ReturnCodes { Success, Failure, NonAttachedEngine };
	bool CheckAttachedEngine() const;
	int RunTest();
	/*----------------STATE-CONTROL---------------------*/

protected:
	Engine* ptr_engine = nullptr;

	/*----------------RESULT-FIELDS---------------------*/
	float test_time = 0.0f;
	/*----------------RESULT-FIELDS---------------------*/

	/*------------HIDDEN-STATE-CONTROL------------------*/
	virtual int MakeStep() = 0;
	/*------------HIDDEN-STATE-CONTROL------------------*/
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

	/*----------------STATE-CONTROL---------------------*/
	enum ReturnCodes { Success, Failure, NonAttachedEngine, NonOverheat };
	/*----------------STATE-CONTROL---------------------*/

protected:
	/*------------HIDDEN-STATE-CONTROL------------------*/
	bool CheckOverheat() const;
	bool CheckOverheatReachability() const;
	void UpdateMaxTemperature();
	int MakeStep() override;
	/*------------HIDDEN-STATE-CONTROL------------------*/

	/*----------------RESULT-FIELDS---------------------*/
	float engine_max_temperature = -FLT_MAX;
	/*----------------RESULT-FIELDS---------------------*/
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
	/*------------HIDDEN-STATE-CONTROL------------------*/
	bool CheckOverVelocity() const;
	void UpdateMaxPower();
	void UpdateMaxVelocity();
	int MakeStep() override;
	/*------------HIDDEN-STATE-CONTROL------------------*/

	/*----------------RESULT-FIELDS---------------------*/
	float engine_max_power = -FLT_MAX;
	float engine_max_velocity = -FLT_MAX;
	float engine_velocity_at_max_power = -FLT_MAX;
	/*----------------RESULT-FIELDS---------------------*/
};

