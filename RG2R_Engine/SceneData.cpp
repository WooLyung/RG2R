#include "stdafx.h"
#include "SceneData.h"

SceneData* SceneData::GetInstance()
{
	static auto sceneData = SceneData();
	return &sceneData;
}