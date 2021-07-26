#include "stdafx.h"
#include "IntroManager.h"
#include "CommandList.h"
#include "Engine.h"
#include "TitleScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "SoundMaster.h"
#include <thread>

void LoadSound() {
	RG2R_SoundM->Load("Resources/Sounds/lift.wav");
	RG2R_SoundM->Load("Resources/Sounds/line_connect.wav");
	RG2R_SoundM->Load("Resources/Sounds/drop.wav");
	RG2R_SoundM->Load("Resources/Sounds/click.wav");
	RG2R_SoundM->Load("Resources/Sounds/slide.wav");
	RG2R_SoundM->Load("Resources/Sounds/bgm.ogg");
}

IntroManager::IntroManager()
{
}

IntroManager::~IntroManager()
{
}

void IntroManager::OnStart()
{
	black = CreateObject();
	black->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/black.png")
		->SetZ_index(-1);
	black->GetComponent<Transform>()
		->SetAnchor(64, 36)
		->SetScale(15, 15);
	effect = black->AttachComponent<Effect>();

	textRenderer = AttachComponent<TextRenderer>()
		->SetText("절대우승해 제작")->SetTextColor(Color(1, 1, 1, 0))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
}

void IntroManager::OnUpdate()
{
	time += RG2R_TimeM->GetDeltaTime();

	if (state == IntroState::sans)
	{
		if (time >= 0.5f)
		{
			std::thread t(&LoadSound);
			t.join();
			state = IntroState::firstWait;
			time = 0;
		}
	}
	if (state == IntroState::firstWait)
	{
		if (time >= 3)
		{
			state = IntroState::appear1;
			time = 0;
		}
	}
	else if (state == IntroState::appear1)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::wait1;
			time = 0;
		}
	}
	else if (state == IntroState::wait1)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1));

		if (time >= 1.5f)
		{
			state = IntroState::disappear1;
			time = 0;
		}
	}
	else if (state == IntroState::disappear1)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1 - time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::textWait;
			time = 0;
		}
	}
	else if (state == IntroState::textWait)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 0));

		if (time >= 1.5f)
		{
			state = IntroState::appear2;
			textRenderer->SetText("Republic of Game");
			time = 0;
		}
	}
	else if (state == IntroState::appear2)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::wait2;
			time = 0;
		}
	}
	else if (state == IntroState::wait2)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1));

		if (time >= 1.5f)
		{
			state = IntroState::disappear2;
			time = 0;
		}
	}
	else if (state == IntroState::disappear2)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1 - time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::nextWait;
			textRenderer->SetTextColor(Color(1, 1, 1, 0));
			time = 0;
		}
	}
	else if (state == IntroState::nextWait)
	{
		effect->ClearEffectInfo()
			->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1 - time * 2)));

		if (time >= 0.5f)
		{
			RG2R_SceneM->ChangeScene(new TitleScene, true);
			SoundMaster::GetInstance()->PlayBGM();
		}
	}
}