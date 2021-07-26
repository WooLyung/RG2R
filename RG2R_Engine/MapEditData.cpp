#include "stdafx.h"
#include "MapEditData.h"

MapEditData* MapEditData::GetInstance()
{
	static auto mapData = MapEditData();
	return &mapData;
}