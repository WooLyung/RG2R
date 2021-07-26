#include "stdafx.h"
#include "SettingBoard.h"
#include "Engine.h"
#include "ViewRenderer.h"
#include "Settings.h"
#include "SettingData.h"

SettingBoard::SettingBoard(ChapterScene* scene)
{
	this->scene = scene;
}

SettingBoard::~SettingBoard()
{
}

void SettingBoard::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_board.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(41);
	transform = GetComponent<Transform>()
		->SetScale(0.6f, 0.6f)
		->SetIsRelative(false)
		->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		time += RG2R_TimeM->GetDeltaTime() * 1.5f;
		transform->SetPosY((GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.9f)
			* (time - 1) * (time - 1));

		blurEffect->ClearEffectInfo()
			->PushEffectInfo(new GaussianBlurEffectInfo(time * 2.5f))
			->PushEffectInfo(new ColorMatrixEffectInfo(Color(1 - time * 0.2f, 1 - time * 0.2f, 1 - time * 0.2f)));

		if (time >= 1)
		{
			boardState = BoardState::wait;
			time = 0;
			appearAnim->Stop();
			transform->SetPosY(0);
		}
		}, 0);
	appearAnim->SetIsLoop(true);

	startAnim = new CommandList;
	commandLists.push_back(startAnim);
	startAnim->PushCommand([=]() {
		transform->Translate(0, -RG2R_TimeM->GetDeltaTime());
		if (transform->GetPos().y <= GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.9f)
		{
			boardState = BoardState::top;
			time = 0;
			startAnim->Stop();
			transform->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.9f);
		}
		}, 0);
	startAnim->SetIsLoop(true);
	startAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		time += RG2R_TimeM->GetDeltaTime() * 1.5f;
		transform->SetPosY((GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.9f)
			* time * time);

		blurEffect->ClearEffectInfo()
			->PushEffectInfo(new GaussianBlurEffectInfo((1 - time) * 2.5f))
			->PushEffectInfo(new ColorMatrixEffectInfo(Color(time * 0.2f + 0.8f, time * 0.2f + 0.8f, time * 0.2f + 0.8f)));

		if (time >= 1)
		{
			boardState = BoardState::top;
			time = 0;
			disappearAnim->Stop();
			transform->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.9f);
		}
		}, 0);
	disappearAnim->SetIsLoop(true);

	changeScene = new CommandList;
	commandLists.push_back(changeScene);
	changeScene->PushCommand([=]() {
		transform->Translate(0, RG2R_TimeM->GetDeltaTime());
		}, 0);
	changeScene->SetIsLoop(true);

	blur = CreateObject();
	blurEffect = blur->AttachComponent<Effect>();

	blur->GetComponent<Transform>()
		->SetIsRelative(false)
		->SetAnchor(INCH_PER_DISTANCE * 8, INCH_PER_DISTANCE * 4);
	auto view = blur->AttachComponent<ViewRenderer>()
		->SetCamera(GetScene()->GetMainCamera())
		->SetSize(Size2U(INCH_PER_DISTANCE * 16, INCH_PER_DISTANCE * 8));
	view->SetZ_index(40);

	CreateElements();
}

void SettingBoard::OnUpdate()
{
	Input();
}

void SettingBoard::CreateElements()
{
	// BGM 소리
	Object* sound_bgm = new Object;
	auto sound_bgm_spr = sound_bgm->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_checkbox.png");
	sound_bgm_spr->SetZ_index(42);
	auto sound_bgm_trs = sound_bgm->GetComponent<Transform>()
		->SetAnchor(sound_bgm_spr->GetTexture()->GetSize().width * 0.5f, sound_bgm_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.32f, 0.32f)
		->SetPos(2, 1.33f);
	Object* sound_bgm_check = new Object;
	auto sound_bgm_check_spr = sound_bgm_check->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_check.png");
	sound_bgm_check_spr->SetZ_index(43);
	sound_bgm_check_spr->SetIsEnable(SettingData::GetInstance()->sound_bgm);
	sound_bgm_check->GetComponent<Transform>()
		->SetAnchor(sound_bgm_check_spr->GetTexture()->GetSize().width * 0.5f, sound_bgm_check_spr->GetTexture()->GetSize().height * 0.5f)
		->SetPos(0.05f, 0.65f);
	sound_bgm->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (sound_bgm_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				SettingData::GetInstance()->SetData(1, !SettingData::GetInstance()->sound_bgm);
				sound_bgm_check_spr->SetIsEnable(SettingData::GetInstance()->sound_bgm);
			}
		}
	};
	sound_bgm->AttachChild(sound_bgm_check);
	AttachChild(sound_bgm);

	// 효과음
	Object* sound_effect = new Object;
	auto sound_effect_spr = sound_effect->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_checkbox.png");
	sound_effect_spr->SetZ_index(42);
	auto sound_effect_trs = sound_effect->GetComponent<Transform>()
		->SetAnchor(sound_effect_spr->GetTexture()->GetSize().width * 0.5f, sound_effect_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.32f, 0.32f)
		->SetPos(2, 0.85f);
	Object* sound_effect_check = new Object;
	auto sound_effect_check_spr = sound_effect_check->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_check.png");
	sound_effect_check_spr->SetZ_index(43);
	sound_effect_check_spr->SetIsEnable(SettingData::GetInstance()->sound_effect);
	sound_effect_check->GetComponent<Transform>()
		->SetAnchor(sound_effect_check_spr->GetTexture()->GetSize().width * 0.5f, sound_effect_check_spr->GetTexture()->GetSize().height * 0.5f)
		->SetPos(0.05f, 0.65f);
	sound_effect->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (sound_effect_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				SettingData::GetInstance()->SetData(2, !SettingData::GetInstance()->sound_effect);
				sound_effect_check_spr->SetIsEnable(SettingData::GetInstance()->sound_effect);
			}
		}
	};
	sound_effect->AttachChild(sound_effect_check);
	AttachChild(sound_effect);

	// 이펙트
	Object* effect = new Object;
	auto effect_spr = effect->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_checkbox.png");
	effect_spr->SetZ_index(42);
	auto effect_trs = effect->GetComponent<Transform>()
		->SetAnchor(effect_spr->GetTexture()->GetSize().width * 0.5f, effect_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.32f, 0.32f)
		->SetPos(2, -0.12f);
	Object* effect_check = new Object;
	auto effect_check_spr = effect_check->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_check.png");
	effect_check_spr->SetZ_index(43);
	effect_check_spr->SetIsEnable(SettingData::GetInstance()->effect);
	effect_check->GetComponent<Transform>()
		->SetAnchor(effect_check_spr->GetTexture()->GetSize().width * 0.5f, effect_check_spr->GetTexture()->GetSize().height * 0.5f)
		->SetPos(0.05f, 0.65f);
	effect->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (effect_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				SettingData::GetInstance()->SetData(3, !SettingData::GetInstance()->effect);
				effect_check_spr->SetIsEnable(SettingData::GetInstance()->effect);
			}
		}
	};
	effect->AttachChild(effect_check);
	AttachChild(effect);

	// 풀스크린
	Object* fullscreen = new Object;
	auto fullscreen_spr = fullscreen->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_checkbox.png");
	fullscreen_spr->SetZ_index(42);
	auto fullscreen_trs = fullscreen->GetComponent<Transform>()
		->SetAnchor(fullscreen_spr->GetTexture()->GetSize().width * 0.5f, fullscreen_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.32f, 0.32f)
		->SetPos(2, -0.61f);
	Object* fullscreen_check = new Object;
	auto fullscreen_check_spr = fullscreen_check->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_check.png");
	fullscreen_check_spr->SetZ_index(43);
	fullscreen_check_spr->SetIsEnable(SettingData::GetInstance()->fullscreen);
	fullscreen_check->GetComponent<Transform>()
		->SetAnchor(fullscreen_check_spr->GetTexture()->GetSize().width * 0.5f, fullscreen_check_spr->GetTexture()->GetSize().height * 0.5f)
		->SetPos(0.05f, 0.65f);
	fullscreen->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (fullscreen_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				SettingData::GetInstance()->SetData(4, !SettingData::GetInstance()->fullscreen);
				fullscreen_check_spr->SetIsEnable(SettingData::GetInstance()->fullscreen);
			}
		}
	};
	fullscreen->AttachChild(fullscreen_check);
	AttachChild(fullscreen);

	// 해상도 표시
	Object* resolution = new Object;
	auto resolution_spr = resolution->AttachComponent<SpriteRenderer>();
	resolution_spr->SetZ_index(42);
	if (SettingData::GetInstance()->resolution == 1)
		resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level1.png");
	else if (SettingData::GetInstance()->resolution == 2)
		resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level2.png");
	else if (SettingData::GetInstance()->resolution == 3)
		resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level3.png");
	else if (SettingData::GetInstance()->resolution == 4)
		resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level4.png");
	auto resolution_trs = resolution->GetComponent<Transform>()
		->SetAnchor(resolution_spr->GetTexture()->GetSize().width * 0.5f, resolution_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.24f, 0.24f)
		->SetPos(0, -1.58f);
	AttachChild(resolution);

	// 해상도 증가
	Object* resolution_up = new Object;
	auto resolution_up_spr = resolution_up->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_up.png");
	resolution_up_spr->SetZ_index(42);
	auto resolution_up_trs = resolution_up->GetComponent<Transform>()
		->SetAnchor(resolution_up_spr->GetTexture()->GetSize().width * 0.5f, resolution_up_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.24f, 0.24f)
		->SetPos(2, -1.58f);
	resolution_up->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (resolution_up_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				int level = SettingData::GetInstance()->resolution;
				level++;
				if (level > 4) level = 4;
				SettingData::GetInstance()->SetData(5, level);

				if (SettingData::GetInstance()->resolution == 1)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level1.png");
				else if (SettingData::GetInstance()->resolution == 2)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level2.png");
				else if (SettingData::GetInstance()->resolution == 3)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level3.png");
				else if (SettingData::GetInstance()->resolution == 4)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level4.png");

				resolution->GetComponent<Transform>()
					->SetAnchor(resolution_spr->GetTexture()->GetSize().width * 0.5f, resolution_spr->GetTexture()->GetSize().height * 0.5f)
					->SetScale(0.24f, 0.24f)
					->SetPos(0, -1.58f);
			}
		}
	};
	AttachChild(resolution_up);

	// 해상도 감소
	Object* resolution_down = new Object;
	auto resolution_down_spr = resolution_down->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_down.png");
	resolution_down_spr->SetZ_index(42);
	auto resolution_down_trs = resolution_down->GetComponent<Transform>()
		->SetAnchor(resolution_down_spr->GetTexture()->GetSize().width * 0.5f, resolution_down_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.24f, 0.24f)
		->SetPos(-2, -1.58f);
	resolution_down->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (resolution_down_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				int level = SettingData::GetInstance()->resolution;
				level--;
				if (level < 1) level = 1;
				SettingData::GetInstance()->SetData(5, level);

				if (SettingData::GetInstance()->resolution == 1)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level1.png");
				else if (SettingData::GetInstance()->resolution == 2)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level2.png");
				else if (SettingData::GetInstance()->resolution == 3)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level3.png");
				else if (SettingData::GetInstance()->resolution == 4)
					resolution_spr->SetTexture("Resources/Sprites/UIs/Settings/Resolutions/resolution_level4.png");

				resolution->GetComponent<Transform>()
					->SetAnchor(resolution_spr->GetTexture()->GetSize().width * 0.5f, resolution_spr->GetTexture()->GetSize().height * 0.5f)
					->SetScale(0.24f, 0.24f)
					->SetPos(0, -1.58f);
			}
		}
	};
	AttachChild(resolution_down);

	// 완료
	Object* done = new Object;
	auto done_spr = done->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_done.png");
	done_spr->SetZ_index(42);
	auto done_trs = done->GetComponent<Transform>()
		->SetAnchor(done_spr->GetTexture()->GetSize().width * 0.5f, done_spr->GetTexture()->GetSize().height * 0.5f)
		->SetScale(0.24f, 0.24f)
		->SetPos(0, -3.02f);
	done->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (done_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.35f)
		{
			if (boardState == BoardState::wait && RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				disappearAnim->Start();
				boardState = BoardState::disappear;
			}
		}
	};
	AttachChild(done);
}

void SettingBoard::Input()
{
	Vec2F vec = RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos());

	if (boardState == BoardState::top
		&& vec.y >= transform->GetPos().y - 2.7f
		&& vec.y <= transform->GetPos().y - 2
		&& vec.x <= 1 && vec.x >= -1)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE)
		{
			if (inputState == InputState::none)
			{
				inputState = InputState::hover;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			if (inputState == InputState::hover)
			{
				inputState = InputState::click;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (inputState == InputState::click)
			{
				appearAnim->Start();
				boardState = BoardState::appear;
			}
		}
	}
	else
	{
		inputState = InputState::none;
	}

	if (boardState == BoardState::wait
		&& RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER)
	{
		disappearAnim->Start();
		boardState = BoardState::disappear;
	}
}