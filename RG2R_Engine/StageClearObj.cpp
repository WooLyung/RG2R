#include "stdafx.h"
#include "StageClearObj.h"
#include "Engine.h"
#include "ToNextButton.h"
#include "SceneData.h"
#include "SoundMaster.h"

StageClearObj::StageClearObj(InGameScene* scene)
{
	this->scene = scene;
	GetComponent<Transform>()->SetPos(50, 50);
}

StageClearObj::~StageClearObj()
{
}

void StageClearObj::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Clear/clear.png");
	spriteRenderer->SetZ_index(1000);
	transform = GetComponent<Transform>()
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f,
			spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetIsRelative(false)
		->SetScale(0.6f, 0.6f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f + 1
			- (-pow(animTime - 1, 2) + 1) * 2.25f, 0.2f);
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();
	SoundMaster::GetInstance()->PlayEffectSound(SoundID::SLIDE);

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime -= RG2R_TimeM->GetDeltaTime();

		if (animTime <= 0)
		{
			animTime = 0;
			disappearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f + 1
			- (-pow(animTime - 1, 2) + 1) * 2.25f, 0.2f);
		}, 0);
	disappearAnim->SetIsLoop(true);
}

void StageClearObj::OnUpdate()
{

}

void StageClearObj::Disappear()
{
	SceneData::GetInstance()->inGameCode = 0;
	scene->postit->Disappear();
	scene->playButton->Disappear();
	scene->resetButton->Disappear();
	scene->menuButton->Disappear();
	scene->editButton->Disappear();
	scene->tiles->Down();
	scene->sceneChangeManager->Diff();
	disappearAnim->Start();
}