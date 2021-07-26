#include "stdafx.h"
#include "PostIt.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "Effect.h"

PostIt::PostIt(bool isAnim)
{
	this->isAnim = isAnim;

	auto textObj = new Object;
	textRenderer = textObj->AttachComponent<TextRenderer>()
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER)
		->SetTextColor(Color(1, 1, 1))
		->SetText("¾È³çÇÏ¼¼¿ä!")
		->SetSize(25);
	textRenderer->SetZ_index(10);
	AttachChild(textObj);
}

PostIt::~PostIt()
{
}

void PostIt::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/postit.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.8f, 0.8f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetIsRelative(false);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.9f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.9f);
		transform->SetRot(20 - (pow(animTime - 1, 2) + 1) * 50);

		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			disappearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.9f - pow(animTime, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.9f);
		transform->SetRot(-30 + pow(animTime, 2) * 100);
		}, 0);
	disappearAnim->SetIsLoop(true);

	if (!isAnim)
	{
		animTime = 1;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.9f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.9f);
		transform->SetRot(20 - (pow(animTime - 1, 2) + 1) * 50);
	}
}

void PostIt::OnUpdate()
{
}

Transform* PostIt::GetTransform()
{
	return transform;
}

SpriteRenderer* PostIt::GetSpriteRenderer()
{
	return spriteRenderer;
}

TextRenderer* PostIt::GetTextRenderer()
{
	return textRenderer;
}

void PostIt::Disappear()
{
	disappearAnim->Start();
	animTime = 0;
}