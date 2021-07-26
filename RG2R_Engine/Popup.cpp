#include "stdafx.h"
#include "Popup.h"
#include "Engine.h"

Popup::Popup()
{
}

Popup::~Popup()
{
}

void Popup::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/PopUps/notComplete.png");
	transform = GetComponent<Transform>()
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, 0)
		->SetIsRelative(false)
		->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f + 3)
		->SetScale(0.4f, 0.4f);

	pop = new CommandList;
	pop->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 2.5f)
		{
			pop->Stop();
		}
		else if (animTime >= 1.5f)
		{
			float time = animTime - 1.5f;
			transform->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f + pow(time, 2) * 3);
		}
		else if (animTime >= 0.5f)
		{
			transform->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f);
		}
		else
		{
			float time = 1 - animTime * 2;
			transform->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f + pow(time, 2) * 3);
		}
		}, 0);
	pop->SetIsLoop(true);
	commandLists.push_back(pop);
}

void Popup::Pop(int code)
{
	if (code == 0)
	{
		animTime = 0;
		pop->Start();
		spriteRenderer->SetTexture("Resources/Sprites/UIs/PopUps/notComplete.png");
	}
	else if (code == 1)
	{
		animTime = 0;
		pop->Start();
		spriteRenderer->SetTexture("Resources/Sprites/UIs/PopUps/cycle.png");
	}
	else if (code == 2)
	{
		animTime = 0;
		pop->Start();
		spriteRenderer->SetTexture("Resources/Sprites/UIs/PopUps/stageFail.png");
	}
}