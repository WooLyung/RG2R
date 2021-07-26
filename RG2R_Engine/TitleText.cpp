#include "stdafx.h"
#include "TitleText.h"
#include "Engine.h"
#include "ChapterScene.h"

TitleText::TitleText()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/titleText.png");
	transform = GetComponent<Transform>()
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f,
			spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.55f, 0.55f);


	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPosY(-pow(animTime - 1, 2) * 5);

		if (animTime >= 1)
		{
			transform->SetPosY(0);
			animTime = 1;
			appearAnim->Stop();
		}
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime -= RG2R_TimeM->GetDeltaTime();
		transform->SetPosY(-pow(animTime - 1, 2) * 5);
		}, 0);
	disappearAnim->SetIsLoop(true);
}

TitleText::~TitleText()
{
}

void TitleText::NextScene()
{
	disappearAnim->Start();
}