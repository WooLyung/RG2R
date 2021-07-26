#include "stdafx.h"
#include "ObjectManager.h"
#include "Line.h"

ObjectManager::ObjectManager(InGameScene* scene)
{
	this->scene = scene;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::OnStart()
{
}

void ObjectManager::SetSpriteOnConnect(Line* lastLine, Line* newLine, Vec2L tilePos)
{
	// todo
}

void ObjectManager::SetSpriteOnFinish(Line* line, Vec2L tilePos)
{	
	//todo
}

void ObjectManager::PushGate(Gate* gate)
{
	gates.push_back(gate);
}

Line* ObjectManager::FindLine(Vec2L pos)
{
	Line* target = nullptr;

	for (auto& iter : lines)
		if (iter->tilePos == pos)
			target = iter;

	return target;
}

Gate* ObjectManager::FindGate(Vec2L pos)
{
	Gate* target = nullptr;

	for (auto& iter : gates)
		if (iter->tilePos == pos)
			target = iter;

	return target;
}