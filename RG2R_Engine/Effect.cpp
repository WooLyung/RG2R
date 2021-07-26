#include "stdafx.h"
#include "Effect.h"
#include "ViewRenderData.h"

Effect::Effect()
{
}

Effect::~Effect()
{
	for (auto i : effects_)
		delete i;
}

Effect* Effect::PushEffectInfo(EffectInfo * effectInfo)
{
	effects_.push_back(effectInfo);
	return this;
}

Effect* Effect::ClearEffectInfo()
{
	for (auto& iter : effects_)
	{
		delete iter;
	}
	effects_.clear();
	return this;
}

Effect* Effect::PopEffectInfo()
{
	delete effects_.back();
	effects_.pop_back();

	return this;
}

ID2D1Image* Effect::GetOutputImage(ID2D1Image * input)
{
	if (effects_.empty())
		return input;

	for (auto i : effects_)
		input = i->GetOutputImage(input);

	return input;
}

void Effect::Update()
{

}

void Effect::Render()
{

}

void Effect::Render(ViewRenderData&)
{

}