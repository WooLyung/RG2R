#pragma once
#include <string>
#include <list>

struct GateData
{
	int x, y;
	std::string texture;
	std::string color;
	std::string dir;
	std::string type;
	bool isStatic = false;
};

class MapEditData
{
public:
	static MapEditData* GetInstance();

	std::list<GateData> gates;
	float zoom;
	int width, height;
	int playType = 0; // 0일반 1테스트 2플레이
};