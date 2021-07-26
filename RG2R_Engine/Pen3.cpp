#include "stdafx.h"
#include "Pen3.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

Pen3::Pen3(bool isAnim)
{
	this->isAnim = isAnim;
}

Pen3::~Pen3()
{
}

void Pen3::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/pen3.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.8f, 0.8f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width, spriteRenderer->GetTexture()->GetSize().height)
		->SetIsRelative(false)
		->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.4f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 0.7f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.4f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 0.7f - pow(animTime - 1, 2) * 5);
		transform->SetRot(-120 - (pow(animTime - 1, 2) + 1) * -120);

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
			transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.4f,
				GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 0.7f - pow(animTime - 1, 2) * 5);
			transform->SetRot(-120 - (pow(animTime - 1, 2) + 1) * -120);
		}
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	if (!isAnim)
	{
		animTime = 1;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.4f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 0.7f - pow(animTime - 1, 2) * 5);
		transform->SetRot(-120 - (pow(animTime - 1, 2) + 1) * -120);
	}
}

void Pen3::OnUpdate()
{
}

Transform* Pen3::GetTransform()
{
	return transform;
}

SpriteRenderer* Pen3::GetSpriteRenderer()
{
	return spriteRenderer;
}