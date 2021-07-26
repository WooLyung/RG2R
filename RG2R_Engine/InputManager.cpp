#include "stdafx.h"
#include "Engine.h"
#include "InputManager.h"
#include "Settings.h"

InputManager::InputManager()
	:keyStateL_{0,}, // keyState를 이전과 현재 모두 0으로 초기화시킴
	keyStateR_{0,}
{
	// directInput_ 변수에 Direct Input 객체를 담아옴
	DirectInput8Create(GetModuleHandleA(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8A, (void**)&directInput_, nullptr);

	// Keyboard 객체 받아옴
	directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, nullptr); // 키보드 디바이스 새로 생성
	keyboard_->SetDataFormat(&c_dfDIKeyboard); // 데이터 포맷을 키보드로
	keyboard_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	// 백그라운드에서는 사용하지 않음, 장치를 사용하고 있을 동안 뺏기지 않음
	keyboard_->Acquire();

	// Mouse 객체 받아옴
	directInput_->CreateDevice(GUID_SysMouse, &mouse_, nullptr); // 마우스 디바이스 새로 생성
	mouse_->SetDataFormat(&c_dfDIMouse); // 데이터 포맷을 마우스로
	//mouse_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	mouse_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	// 백그라운드에서는 사용하지 않음, 같은 장치를 사용하고 있는 다른 프로그램을 방해하지 않음
	mouse_->Acquire();
}
InputManager::~InputManager()
{
	if (mouse_) // 마우스 객체가 존재할 때
	{
		mouse_->Unacquire();
		mouse_->Release();
	}
	if (keyboard_) // 키보드 객체가 존재할 때
	{
		keyboard_->Unacquire();
		keyboard_->Release();
	}
	if (directInput_) // Direct Input 객체가 존재할 때
	{
		directInput_->Release();
	}
}

void InputManager::Update(void)
{
	HRESULT result = 0;
	memcpy_s(keyStateL_, sizeof(keyStateL_), keyStateR_, sizeof(keyStateR_));
	result = keyboard_->GetDeviceState(sizeof(keyStateR_), (LPVOID)&keyStateR_);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard_->Acquire();
		}
	}

	memcpy_s(rgbButtonsL_, sizeof(rgbButtonsL_), mouseState_.rgbButtons, sizeof(mouseState_.rgbButtons));
	result = mouse_->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState_);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mouse_->Acquire();
		}
	}
}

#define LKEY(key) (keyStateL_[key] & 0x80 ? true : false)
#define RKEY(key) (keyStateR_[key] & 0x80 ? true : false)

KeyState InputManager::GetKeyState(KeyCode key)
{
	if (LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_STAY;
	if (!LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_ENTER;
	if (LKEY(key) && !RKEY(key)) return KeyState::KEYSTATE_EXIT;
	return KeyState::KEYSTATE_NONE;
}

#undef LKEY
#undef RKEY

#define LKEY(key) (rgbButtonsL_[key] & 0x80 ? true : false)
#define RKEY(key) (mouseState_.rgbButtons[key] & 0x80 ? true : false)

KeyState InputManager::GetMouseState(MouseCode key)
{
	if (LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_STAY;
	if (!LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_ENTER;
	if (LKEY(key) && !RKEY(key)) return KeyState::KEYSTATE_EXIT;
	return KeyState::KEYSTATE_NONE;
}

#undef LKEY
#undef RKEY

Point2F InputManager::GetMousePos() const
{
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(RG2R_WindowM->GetHwnd(), &mousePoint);
	return Point2F(mousePoint.x, mousePoint.y);
}

Point2F InputManager::GetMouseWorldPos() const
{
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(RG2R_WindowM->GetHwnd(), &mousePoint);

	float translationRatio = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)
		/ (INCH_PER_DISTANCE * INCH_PER_DISTANCE * DIAGONAL_LENGTH * DIAGONAL_LENGTH)
	);

	Matrix matrix =
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / -2.f, RG2R_WindowM->GetSize().height / -2.f)*
		D2D1::Matrix3x2F::Scale(1 / RG2R_SceneM->GetScene()->GetMainCamera()->GetZoom().x, 1 / RG2R_SceneM->GetScene()->GetMainCamera()->GetZoom().y) *
		D2D1::Matrix3x2F(RG2R_SceneM->GetScene()->GetMainCamera()->GetIsFlipX() ? -1 : 1, 0, 0, RG2R_SceneM->GetScene()->GetMainCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Rotation(RG2R_SceneM->GetScene()->GetMainCamera()->GetRot()) *
		D2D1::Matrix3x2F::Scale(1 / translationRatio, 1 / translationRatio) *
		D2D1::Matrix3x2F::Translation(RG2R_SceneM->GetScene()->GetMainCamera()->GetPos().x * INCH_PER_DISTANCE, -RG2R_SceneM->GetScene()->GetMainCamera()->GetPos().y * INCH_PER_DISTANCE);

	float x = mousePoint.x;
	float y = mousePoint.y;

	return Point2F(
		(x * matrix._11 + y * matrix._21 + matrix._31) / INCH_PER_DISTANCE,
		-(x * matrix._12 + y * matrix._22 + matrix._32) / INCH_PER_DISTANCE);
}

long InputManager::GetMouseDeltaX(void) const
{
	return mouseState_.lX;
}

long InputManager::GetMouseDeltaY(void) const
{
	return mouseState_.lY;
}

int InputManager::GetMouseWheel(void) const
{
	return (int)mouseState_.lZ;
}

Vec2F InputManager::FromScreenToUI(Vec2F vec) {
	auto size = RG2R_WindowM->GetSize();
	float d = sqrt(size.width * size.width + size.height * size.height);

	auto resultTmp = (vec - Vec2F(size.width / 2.f, size.height / 2.f)) * DIAGONAL_LENGTH / d;
	return Vec2F(resultTmp.x, -resultTmp.y);
}

Vec2F InputManager::FromUIToScreen(Vec2F vec) {
	auto size = RG2R_WindowM->GetSize();
	float d = sqrt(size.width * size.width + size.height * size.height);
	return Vec2F(vec.x, -vec.y) * d / DIAGONAL_LENGTH + Vec2F(size.width / 2.f, size.height / 2.f);
}

Vec2F InputManager::FromWorldToScreen(Vec2F vec)
{
	return FromUIToScreen(FromWorldToUI(vec));
}

Vec2F InputManager::FromWorldToUI(Vec2F vec)
{
	float translationRatio = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)
		/ (INCH_PER_DISTANCE * INCH_PER_DISTANCE * DIAGONAL_LENGTH * DIAGONAL_LENGTH)
	);

	Matrix matrix =
		D2D1::Matrix3x2F::Translation(-RG2R_SceneM->GetScene()->GetMainCamera()->GetPos().x * INCH_PER_DISTANCE, RG2R_SceneM->GetScene()->GetMainCamera()->GetPos().y * INCH_PER_DISTANCE) *
		D2D1::Matrix3x2F::Scale(translationRatio, translationRatio) *
		D2D1::Matrix3x2F::Rotation(-RG2R_SceneM->GetScene()->GetMainCamera()->GetRot()) *
		D2D1::Matrix3x2F(RG2R_SceneM->GetScene()->GetMainCamera()->GetIsFlipX() ? -1 : 1, 0, 0, RG2R_SceneM->GetScene()->GetMainCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Scale(RG2R_SceneM->GetScene()->GetMainCamera()->GetZoom().x, RG2R_SceneM->GetScene()->GetMainCamera()->GetZoom().y) *
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / 2.f, RG2R_WindowM->GetSize().height / 2.f);

	float x = vec.x * INCH_PER_DISTANCE;
	float y = vec.y * -INCH_PER_DISTANCE;

	return Point2F(
		x * matrix._11 + y * matrix._21 + matrix._31,
		x * matrix._12 + y * matrix._22 + matrix._32);
}

Vec2F InputManager::FromUIToWorld(Vec2F vec)
{
	float translationRatio = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)
		/ (INCH_PER_DISTANCE * INCH_PER_DISTANCE * DIAGONAL_LENGTH * DIAGONAL_LENGTH)
	);

	Matrix matrix =
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / -2.f, RG2R_WindowM->GetSize().height / -2.f)*
		D2D1::Matrix3x2F::Scale(1 / RG2R_SceneM->GetScene()->GetMainCamera()->GetZoom().x, 1 / RG2R_SceneM->GetScene()->GetMainCamera()->GetZoom().y) *
		D2D1::Matrix3x2F(RG2R_SceneM->GetScene()->GetMainCamera()->GetIsFlipX() ? -1 : 1, 0, 0, RG2R_SceneM->GetScene()->GetMainCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Rotation(RG2R_SceneM->GetScene()->GetMainCamera()->GetRot()) *
		D2D1::Matrix3x2F::Scale(1 / translationRatio, 1 / translationRatio) *
		D2D1::Matrix3x2F::Translation(RG2R_SceneM->GetScene()->GetMainCamera()->GetPos().x * INCH_PER_DISTANCE, -RG2R_SceneM->GetScene()->GetMainCamera()->GetPos().y * INCH_PER_DISTANCE);

	float x = vec.x;
	float y = vec.y;

	return Point2F(
		(x * matrix._11 + y * matrix._21 + matrix._31) / INCH_PER_DISTANCE,
		-(x * matrix._12 + y * matrix._22 + matrix._32) / INCH_PER_DISTANCE);
}

Vec2F InputManager::FromScreenToWorld(Vec2F vec)
{
	return FromUIToWorld(FromScreenToUI(vec));
}