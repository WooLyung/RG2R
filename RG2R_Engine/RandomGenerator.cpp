#include "stdafx.h"
#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
{
	std::random_device rd;
	engine = std::default_random_engine(rd());
}

RandomGenerator::~RandomGenerator()
{
}

int RandomGenerator::GetInt(int from, int to)
{
	std::uniform_int_distribution<int> d(from, to);
	return d(engine);
}

float RandomGenerator::GetFloat(float from, float to)
{
	std::uniform_real_distribution<float> d(from, to);
	return d(engine);
}

double RandomGenerator::GetDouble(double from, double to)
{
	std::uniform_real_distribution<double> d(from, to);
	return d(engine);
}

RandomGenerator* RandomGenerator::GetInstance()
{
	static RandomGenerator instance_ = RandomGenerator();
	return &instance_;
}