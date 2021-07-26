#include "stdafx.h"
#include "Pen1.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "SoundMaster.h"

Pen1::Pen1(bool isAnim)
{
	this->isAnim = isAnim;
}

Pen1::~Pen1()
{
}

void Pen1::OnStart()
{
	SoundMaster::GetInstance()->PlayEffectSound(SoundID::SLIDE);

	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/pen1.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.6f, 0.6f)
		->SetAnchor(0, 0)
		->SetIsRelative(false)
		->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f - 0.4f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f - 0.4f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f);
		transform->SetRot(50 -(pow(animTime - 1, 2) + 1) * 50);

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
			transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f - 0.4f - pow(animTime - 1, 2) * 5,
				GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f);
			transform->SetRot(50 - (pow(animTime - 1, 2) + 1) * 50);
		}
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	if (!isAnim)
	{
		animTime = 1;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f - 0.4f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f);
		transform->SetRot(50 - (pow(animTime - 1, 2) + 1) * 50);
	}
}

void Pen1::OnUpdate()
{
}

Transform* Pen1::GetTransform()
{
	return transform;
}

SpriteRenderer* Pen1::GetSpriteRenderer()
{
	return spriteRenderer;
}