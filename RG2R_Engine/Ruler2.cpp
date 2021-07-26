#include "stdafx.h"
#include "Ruler2.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

Ruler2::Ruler2(bool isAnim)
{
	this->isAnim = isAnim;
}

Ruler2::~Ruler2()
{
}

void Ruler2::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/ruler.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(1.2f, 1.2f)
		->SetRot(60)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width, spriteRenderer->GetTexture()->GetSize().height)
		->SetIsRelative(false)
		->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.8f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 1.2f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.8f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 1.2f);
		transform->SetRot(-60 + (pow(animTime - 1, 2) + 1) * 120);

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
			transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.8f - pow(animTime - 1, 2) * 5,
				GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 1.2f);
			transform->SetRot(-60 + (pow(animTime - 1, 2) + 1) * 120);
		}
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	if (!isAnim)
	{
		animTime = 1;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.8f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f - 1.2f);
		transform->SetRot(-60 + (pow(animTime - 1, 2) + 1) * 120);
	}
}

void Ruler2::OnUpdate()
{
}

Transform* Ruler2::GetTransform()
{
	return transform;
}

SpriteRenderer* Ruler2::GetSpriteRenderer()
{
	return spriteRenderer;
}