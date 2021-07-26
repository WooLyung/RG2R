#pragma once
class RandomGenerator
{
private:
	std::default_random_engine engine;
public:
	RandomGenerator();
	~RandomGenerator();

	int GetInt(int from, int to);
	float GetFloat(float from, float to);
	double GetDouble(double from, double to);

	static RandomGenerator* GetInstance();
};