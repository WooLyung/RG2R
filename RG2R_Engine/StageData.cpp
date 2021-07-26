#include "stdafx.h"
#include "StageData.h"

StageData* StageData::GetInstance()
{
	static auto stageData = StageData();
	return &stageData;
}