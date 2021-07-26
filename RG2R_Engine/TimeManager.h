#pragma once
#include <chrono>

class TimeManager
{
private:
	std::chrono::steady_clock::time_point beginTime_;
	std::chrono::steady_clock::time_point endTime_;
	std::chrono::duration<double> duration_;

public:
	TimeManager();
	~TimeManager();

	void Update();
	int GetElapsedTime();
	float GetDeltaTime();
	int GetFrame();
};