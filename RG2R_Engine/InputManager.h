#pragma once
#include"Math.h"
#include"KeyCode.h"
//TODO: rawinput으로 수정
#define KEY_MAXCOUNT  256

#define DIK_MOUSELBUTTON 0 // 좌클릭
#define DIK_MOUSERBUTTON 1 // 우클릭
#define DIK_MOUSEMBUTTON 2 // 휠클릭
#define DIK_MOUSEXBUTTON 3 // 확장버튼클릭

class InputManager
{
private:
	LPDIRECTINPUT8A directInput_; // Direct Input 객체
	LPDIRECTINPUTDEVICE8A keyboard_; // Direct Input Device (키보드)
	LPDIRECTINPUTDEVICE8A mouse_; // Direct Input Device (마우스)

	BYTE keyStateL_[KEY_MAXCOUNT]; // keyState (1프레임 전)
	BYTE keyStateR_[KEY_MAXCOUNT]; // keyState (현재 프레임)
	DIMOUSESTATE mouseState_; // mouseState
	BYTE rgbButtonsL_[4];
public:
	InputManager();
	~InputManager();

	void Update(void); // 업데이트, App의 루프에서 업데이트시킴

	KeyState GetKeyState(KeyCode key); // 키보드 상태
	KeyState GetMouseState(MouseCode key); // 마우스 상태

	Point2F GetMousePos() const; // 마우스 위치
	Point2F GetMouseWorldPos() const; // 마우스 위치
	
	long GetMouseDeltaX(void) const; // 마우스 움직임의 정도
	long GetMouseDeltaY(void) const; // 마우스 움직임의 정도

	// 내릴시( < 0) 음수(-120, -240, -360 ...), 올릴시( > 0) 양수(120, 240, 360 ...)
	int GetMouseWheel(void) const; // 휠

	Vec2F FromScreenToUI(Vec2F);
	Vec2F FromUIToScreen(Vec2F);
	Vec2F FromScreenToWorld(Vec2F);
	Vec2F FromUIToWorld(Vec2F);
	Vec2F FromWorldToUI(Vec2F);
	Vec2F FromWorldToScreen(Vec2F);
};